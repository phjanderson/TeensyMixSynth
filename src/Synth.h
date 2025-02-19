#ifndef Synth_h
#define Synth_h

#include <stdint.h>
#include <vector>

#include "SynthVoice.h"

#include <Audio.h>
#include "effect_ensemble.h"

// number of voices, mostly restricted by the amount of CPU power
// setting this number too high might result in inaccurate MIDI timing or even crashes, especially when using high notes!
// the maximum is 15 as four 4 channel mixers are used to mix all the voices, the last input is used for other purposes
static const uint16_t NUM_VOICES{8};

/**
 * The Synth handles the polyphony of the synthesizer. It passes parameter changes to all voices, handles the LFO and mixes the voices to a single output.
 */
class Synth
{
private:
    // main I2C audio output
    AudioOutputI2S i2s1;

    // voice mixers
    AudioMixer4 voiceMixerL;
    AudioMixer4 voiceMixerR;

    // voice sub mixers
    std::array<AudioMixer4, 4> voiceSubMixersL;
    std::array<AudioMixer4, 4> voiceSubMixersR;
    AudioConnection patchCordVoiceSubMixersL0ToVoiceMixerL0 = AudioConnection(voiceSubMixersL[0], 0, voiceMixerL, 0);
    AudioConnection patchCordVoiceSubMixersL1ToVoiceMixerL1 = AudioConnection(voiceSubMixersL[1], 0, voiceMixerL, 1);
    AudioConnection patchCordVoiceSubMixersL2ToVoiceMixerL2 = AudioConnection(voiceSubMixersL[2], 0, voiceMixerL, 2);
    AudioConnection patchCordVoiceSubMixersL3ToVoiceMixerL3 = AudioConnection(voiceSubMixersL[3], 0, voiceMixerL, 3);
    AudioConnection patchCordVoiceSubMixersR0ToVoiceMixerR0 = AudioConnection(voiceSubMixersR[0], 0, voiceMixerR, 0);
    AudioConnection patchCordVoiceSubMixersR1ToVoiceMixerR1 = AudioConnection(voiceSubMixersR[1], 0, voiceMixerR, 1);
    AudioConnection patchCordVoiceSubMixersR2ToVoiceMixerR2 = AudioConnection(voiceSubMixersR[2], 0, voiceMixerR, 2);
    AudioConnection patchCordVoiceSubMixersR3ToVoiceMixerR3 = AudioConnection(voiceSubMixersR[3], 0, voiceMixerR, 3);

    // add a 1 bit DC offset to prevent a plop/tick sound whenever all voices become silent, probably due to the DAC switching to power-saving mode
    AudioSynthWaveformDc antiPlopOffset;
    AudioConnection patchCordAntiPlopOffset0ToVoiceSubMixersL33 = AudioConnection(antiPlopOffset, 0, voiceSubMixersL[3], 3);
    AudioConnection patchCordAntiPlopOffset0ToVoiceSubMixersR33 = AudioConnection(antiPlopOffset, 0, voiceSubMixersL[3], 3);

    // mono voice mixer used to send audio to the ensemble chorus
    AudioMixer4 voiceMixer;
    AudioConnection patchCordVoiceMixerL0ToVoiceMixer0 = AudioConnection(voiceMixerL, 0, voiceMixer, 0);
    AudioConnection patchCordVoiceMixerR0ToVoiceMixer1 = AudioConnection(voiceMixerR, 0, voiceMixer, 1);

    // effect mixer, mixes the clean and ensemble chorus sound
    AudioMixer4 effectMixerL;
    AudioMixer4 effectMixerR;

    // connect the voice mixers to the effect mixers (for clean sound)
    AudioConnection patchCordVoiceMixerToEffectMixerL0 = AudioConnection(voiceMixerL, 0, effectMixerL, 0);
    AudioConnection patchCordVoiceMixerToEffectMixerR0 = AudioConnection(voiceMixerR, 0, effectMixerR, 0);

    // ensemble chorus
    AudioEffectEnsemble ensemble;

    // connect the mono voice mixer to the ensemble chorus
    AudioConnection patchCordVoiceMixerToEnsemble = AudioConnection(voiceMixer, 0, ensemble, 0);

    // connect the ensemble chorus to the effect mixers (for effect sound)
    AudioConnection patchCordEnsemble0ToEffectMixerL1 = AudioConnection(ensemble, 0, effectMixerL, 1);
    AudioConnection patchCordEnsemble1ToEffectMixerR1 = AudioConnection(ensemble, 1, effectMixerR, 1);

    // connect the effect mixers to the audio output
    AudioConnection patchCordEffectMixerLToI2S1L = AudioConnection(effectMixerL, 0, i2s1, 0);
    AudioConnection patchCordEffectMixerRToI2S1R = AudioConnection(effectMixerR, 0, i2s1, 1);

    // central lfo
    AudioSynthWaveformModulated lfo;

    // lfo shape level
    AudioSynthWaveformDc lfoShape;
    AudioConnection patchCordLfoShape0ToLfo = AudioConnection(lfoShape, 0, lfo, 1);

    // synth voices
    std::array<SynthVoice, NUM_VOICES> synthVoices;

    // waveshaper
    float currentWaveshapeLevel{0.0f};
    static const uint16_t WAVESHAPE_ARRAY_SIZE{513};
    float waveshapeArray[WAVESHAPE_ARRAY_SIZE]{0.0f};

    /**
     * Update the waveshape array using a hyperbolic tangent function based on the current waveshape level.
     */
    void updateWaveshapeArray()
    {
        for (uint16_t index = 0; index < WAVESHAPE_ARRAY_SIZE; index++)
        {
            float x = map((float)index, 0, WAVESHAPE_ARRAY_SIZE - 1, -1.0f, 1.0f);
            waveshapeArray[index] = 0.25f * tanh((1.0f + currentWaveshapeLevel * 64.0f) * x);
        }
    }

public:
    /**
     * Initialize the Synth.
     */
    void initialize()
    {
        // set the mono voice mixer inputs to 0.5f for joining the stereo sound
        voiceMixer.gain(0, 0.5f);
        voiceMixer.gain(1, 0.5f);

        // start the lfo
        lfo.begin(1.0f, 1.0f, WAVEFORM_TRIANGLE);

        // initialize the synth voices and adjust the voice sub mixer gain according to the configured amount of voices
        uint8_t voiceIdx{0};
        float voiceGain = 1.0f / static_cast<float>(synthVoices.size());
        for (auto &synthVoice : synthVoices)
        {
            AudioMixer4 &voiceSubMixerL = voiceSubMixersL[voiceIdx / 4];
            AudioMixer4 &voiceSubMixerR = voiceSubMixersR[voiceIdx / 4];

            uint8_t voiceSubMixerVoiceIdx = voiceIdx % 4;

            synthVoice.initialize(voiceSubMixerL, voiceSubMixerVoiceIdx, voiceSubMixerR, voiceSubMixerVoiceIdx, lfo, 0);

            voiceSubMixerL.gain(voiceSubMixerVoiceIdx, voiceGain);
            voiceSubMixerR.gain(voiceSubMixerVoiceIdx, voiceGain);
            
            voiceIdx++;
        }

        // add a 1 bit DC offset to prevent a plop/tick sound whenever all voices become silent, probably due to the DAC switching to power-saving mode
        antiPlopOffset.amplitude(-1.0f/32768.0f);
    }

    // see SynthVoice.h
    void onNoteOn(uint8_t note, uint8_t velocity)
    {
        // determine the oldest voice (currently in note off state) based on the last note off timestamp
        uint32_t oldestNoteMillis{UINT32_MAX};
        uint16_t oldestVoice{UINT16_MAX};
        
        for (uint16_t voice = 0 ; voice < NUM_VOICES ; voice++)
        {
            SynthVoice &synthVoice = synthVoices[voice];
            if (!synthVoice.getCurrentMidiNoteOn() && synthVoice.getLastNoteOff() < oldestNoteMillis)
            {
                oldestNoteMillis = synthVoice.getLastNoteOff();
                oldestVoice = voice;
            }
        }

        if (oldestVoice < UINT16_MAX)
        {
            // found voices in note off state, reuse the oldest voice
            synthVoices[oldestVoice].onNoteOn(note, velocity);

            // Serial.print("Reusing voice with oldest note off ");
            // Serial.println(oldestVoice);

            return;
        }

        // no voice in note off state found, determine the oldest voice based on the last note on timestamp
        for (uint16_t voice = 0 ; voice < NUM_VOICES ; voice++)
        {
            SynthVoice &synthVoice = synthVoices[voice];
            if (synthVoice.getLastNoteOn() < oldestNoteMillis)
            {
                oldestNoteMillis = synthVoice.getLastNoteOff();
                oldestVoice = voice;
            }
        }

        if (oldestVoice < UINT16_MAX)
        {
            // reuse the oldest voice
            synthVoices[oldestVoice].onNoteOn(note, velocity);

            // Serial.print("Reusing voice with oldest note on ");
            // Serial.println(oldestVoice);

            return;
        }
    }

    // see SynthVoice.h
    void onNoteOff(uint8_t note)
    {
        for (auto &synthVoice : synthVoices)
        {
            // find voices in note on state with the same note as the one passed to this method
            if (synthVoice.getCurrentMidiNoteOn() && synthVoice.getCurrentMidiNote() == note)
            {
                synthVoice.onNoteOff(note);
            }
        }
    }

    // see SynthVoice.h
    void onSustainToggle(bool on)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.onSustainToggle(on);
        }
    }

    // see SynthVoice.h
    void setPitchChangeRange(uint8_t value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setPitchChangeRange(value);
        }
    }

    // see SynthVoice.h
    void setPitchChange(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setPitchChange(value);
        }
    }

    // see SynthVoice.h
    void setModWhl(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setModWhl(value);
        }
    }

    // see SynthVoice.h
    void logCpuUsageStats()
    {
        synthVoices[0].logCpuUsageStats();
    }

    // envelope 1

    // see SynthVoice.h
    void setEnv1Attack(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnv1Attack(value);
        }
    }

    // see SynthVoice.h
    void setEnv1Decay(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnv1Decay(value);
        }
    }

    // see SynthVoice.h
    void setEnv1Sustain(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnv1Sustain(value);
        }
    }

    // see SynthVoice.h
    void setEnv1Release(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnv1Release(value);
        }
    }

    // envelope 2

    // see SynthVoice.h
    void setEnv2Attack(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnv2Attack(value);
        }
    }

    // see SynthVoice.h
    void setEnv2Decay(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnv2Decay(value);
        }
    }

    // see SynthVoice.h
    void setEnv2Sustain(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnv2Sustain(value);
        }
    }

    // see SynthVoice.h
    void setEnv2Release(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnv2Release(value);
        }
    }

    // filter1

    // see SynthVoice.h
    void setFilter1Frequency(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setFilter1Frequency(value);
        }
    }

    // see SynthVoice.h
    void setFilter1Resonance(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setFilter1Resonance(value);
        }
    }

    // see SynthVoice.h
    void setFilter1KbdTrack(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setFilter1KbdTrack(value);
        }
    }

    // see SynthVoice.h
    void setFilter1KbdVelocity(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setFilter1KbdVelocity(value);
        }
    }

    // see SynthVoice.h
    void setFilter1Env2(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setFilter1Env2(value);
        }
    }

    // see SynthVoice.h
    void setFilter1Lfo(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setFilter1Lfo(value);
        }
    }

    // see SynthVoice.h
    void setFilterMode(uint8_t value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setFilterMode(value);
        }
    }

    // filter2

    // see SynthVoice.h
    void setFilter2FrequencyOffset(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setFilter2FrequencyOffset(value);
        }
    }

    // lfo

    /**
     * Set the LFO frequency.
     * 
     * @param value frequency in Hz
     */
    void setLfoFreq(float value)
    {
        lfo.frequency(value);
    }

    /**
     * Set the shape (for some of the synth waveforms) of the lfo.
     * 
     * @param value shape (0.0f - 1.0f, 0.5f is "normal" shape)
     */
    void setLfoShape(float value)
    {
        lfoShape.amplitude(value, TRANSITION_SPEED_MS);
    }

    /**
     * Set the lfo synth waveform.
     * 
     * @param value synth waveform number
     */
    void setLfoWaveform(uint8_t value)
    {
        auto lfoSynthWaveform = SynthVoice::getSynthWaveformByValue(value);
        if (lfoSynthWaveform.audioWaveform == WAVEFORM_ARBITRARY)
        {
            lfo.arbitraryWaveform(lfoSynthWaveform.waveFormArray, 44100);
        }
        lfo.begin(lfoSynthWaveform.audioWaveform);
    }

    /**
     * Set the lfo attack time.
     * 
     * @param value attack time in milliseconds
     */
    void setEnvLfoAttack(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnvLfoAttack(value);
        }
    }

    // osc 1/fm

    // see SynthVoice.h
    void setOscVolumeMix(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOscVolumeMix(value);
        }
    }

    // see SynthVoice.h
    void setOsc1SynthWaveform(uint8_t value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1SynthWaveform(value);
        }
    }

    // see SynthVoice.h
    void setOscFmSynthWaveform(uint8_t value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOscFmSynthWaveform(value);
        }
    }

    // see SynthVoice.h
    void setOsc1WaveFold(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1WaveFold(value);
        }
    }

    // see SynthVoice.h
    void setOsc1Shape(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1Shape(value);
        }
    }

    // see SynthVoice.h
    void setOscFmOctave(int8_t value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOscFmOctave(value);
        }
    }

    // see SynthVoice.h
    void setOsc1Transpose(int8_t value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1Transpose(value);
        }
    }

    // see SynthVoice.h
    void setOscFmTranspose(int8_t value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOscFmTranspose(value);
        }
    }

    // see SynthVoice.h
    void setOsc1Detune(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1Detune(value);
        }
    }

    // osc 1 mod

    // see SynthVoice.h
    void setOsc1ModFreqEnv2(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1ModFreqEnv2(value);
        }
    }

    // see SynthVoice.h
    void setOsc1ModFreqLfo(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1ModFreqLfo(value);
        }
    }

    // see SynthVoice.h
    void setOsc1ModShapeEnv2(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1ModShapeEnv2(value);
        }
    }

    // see SynthVoice.h
    void setOsc1ModShapeLfo(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1ModShapeLfo(value);
        }
    }

    // see SynthVoice.h
    void setOsc1ModWaveFoldEnv2(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1ModWaveFoldEnv2(value);
        }
    }

    // see SynthVoice.h
    void setOsc1UnisonDetune(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1UnisonDetune(value);
        }
    }

    // see SynthVoice.h
    void setOsc1UnisonMix(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOsc1UnisonMix(value);
        }
    }

    // see SynthVoice.h
    void setOscFmModPhaseEnv2(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOscFmModPhaseEnv2(value);
        }
    }

    // see SynthVoice.h
    void setOscFmPhaseMod(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setOscFmPhaseMod(value);
        }
    }

    // see SynthVoice.h
    void setWaveshapeLevel(float value)
    {
        AudioNoInterrupts();
        currentWaveshapeLevel = value;
        updateWaveshapeArray();
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setWaveshapeLevel(value, waveshapeArray, WAVESHAPE_ARRAY_SIZE);
        }
        AudioInterrupts();
    }

    // see SynthVoice.h
    void setAmpModLfo(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setAmpModLfo(value);
        }
    }

    // see SynthVoice.h
    void setAmpKbdVelocity(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setAmpKbdVelocity(value);
        }
    }

    // see SynthVoice.h
    void setEnvReverse(float value)
    {
        for (auto &synthVoice : synthVoices)
        {
            synthVoice.setEnvReverse(value);
        }
    }

    /**
     * Set the ensemble chorus mix level.
     * 
     * @param value level (0.0f - 1.0f, 0.0f = clean, 1.0f = clean + chorus)
     */
    void setEnsembleMix(float value)
    {
        auto clean = map(value, 0.0f, 1.0f, 1.0f, 0.5f);
        auto wet = map(value, 0.0f, 1.0f, 0.0f, 0.5f);
        effectMixerL.gain(0, clean);
        effectMixerR.gain(0, clean);
        effectMixerL.gain(1, wet);
        effectMixerR.gain(1, wet);
    }

    /**
     * Set the ensemble chorus lfo rate.
     * @param value frequency in Hz
     */
    void setEnsembleLfoRate(float value)
    {
        ensemble.lfoRate(value);
    }
};

#endif