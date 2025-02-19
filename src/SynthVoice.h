#ifndef SynthVoice_h
#define SynthVoice_h

#include <stdint.h>
#include <vector>

#include "Constants.h"
#include "SynthWaveform.h"

#include <Audio.h>

// references to external global constants
extern const std::array<const float, 128> PROGMEM MIDI_NOTE_FREQ;
extern const std::array<const float, 128> PROGMEM PARAM_SCALE_POWER;
extern const float TRANSITION_SPEED_MS;

/**
 * A SynthVoice contains the actual oscillators, envelope generators, filters, etc.
 */
class SynthVoice
{
private:
    // Generated using a modified version of the Audio System Design Tool for Teensy Audio Library
    // https://www.pjrc.com/teensy/gui/
    // modification:
    // https://github.com/PaulStoffregen/Audio/pull/474
    // 
    // You can get a visual representation of the audio nodes and connections by importing the generated part into the Audio System Design Tool.
    // Try to align the coordinates (with shift pressed) to the original coordinates when exporting an updated version.
    // The i2s1 object and two related patch cords need to be commented out, or else there won't be any audio.

    // GUItool: begin automatically generated code
    AudioSynthWaveformDc     dc1Ref;         //xy=130,300
    AudioSynthWaveformDc     osc1Shape;      //xy=140,680
    AudioSynthWaveformDc     oscFmPhaseMod;  //xy=159,1120
    AudioEffectEnvelope      envLfo;      //xy=310,180
    AudioEffectEnvelope      env1;           //xy=310,260
    AudioEffectEnvelope      env2;           //xy=310,340
    AudioEffectMultiply      env1Exp;        //xy=635,260
    AudioMixer4              osc1FreqMixer;  //xy=655,560
    AudioMixer4              osc1ShapeMixer; //xy=660,700
    AudioMixer4              oscFmPhaseModMixer; //xy=680,1140
    AudioSynthWaveformModulated osc1;           //xy=870,620
    AudioSynthWaveformModulated oscFm;          //xy=870,1220
    AudioSynthWaveformModulated osc1Unison1;    //xy=889,700
    AudioSynthWaveformModulated osc1Unison2;    //xy=889,740
    AudioSynthWaveformModulated osc1Unison3;    //xy=889,780
    AudioSynthWaveformModulated osc1Unison4;    //xy=889,820
    AudioSynthWaveformModulated osc1Unison5;    //xy=889,860
    AudioSynthWaveformModulated osc1Unison6;    //xy=889,900
    AudioEffectMultiply      oscFmEnv2Mod;   //xy=899,1100
    AudioSynthWaveformDc     osc1WaveFold;   //xy=1011,520
    AudioMixer4              osc1UnisonMixerL; //xy=1246,760
    AudioMixer4              osc1WaveFoldMixer; //xy=1251,540
    AudioMixer4              osc1UnisonMixerR; //xy=1251,1000
    AudioSynthWaveformDc     kbdTrack;       //xy=1433,180
    AudioSynthWaveformDc     filter1Freq;    //xy=1436,120
    AudioSynthWaveformDc     kbdVelocity;    //xy=1440,240
    AudioEffectWaveFolder    osc1WaveFolder; //xy=1441,620
    AudioMixer4              filter1FreqMixer; //xy=1617,360
    AudioMixer4              filter1FreqSubMixer; //xy=1629,180
    AudioMixer4              oscMixerL;      //xy=1680,760
    AudioMixer4              oscMixerR;      //xy=1681,1000
    AudioSynthWaveformDc     filter2FreqOffset; //xy=1815,120
    AudioAmplifier           filterPreAmpL;  //xy=1871,760
    AudioAmplifier           filterPreAmpR;  //xy=1872,1000
    AudioMixer4              filter2FreqMixer; //xy=2017,180
    AudioFilterStateVariable filter2L;       //xy=2050,800
    AudioFilterStateVariable filter2R;       //xy=2050,1040
    AudioMixer4              filterMixer2L;  //xy=2206,780
    AudioMixer4              filterMixer2R;  //xy=2208,1020
    AudioFilterStateVariable filter1L;       //xy=2350,800
    AudioFilterStateVariable filter1R;       //xy=2350,1040
    AudioMixer4              filterMixer1L;  //xy=2506,780
    AudioMixer4              filterMixer1R;  //xy=2508,1020
    AudioEffectMultiply      env1AmpL;       //xy=2662,780
    AudioEffectMultiply      env1AmpR;       //xy=2663,1020
    AudioFilterStateVariable lfoFilter;      //xy=2831,420
    AudioEffectWaveshaper    waveshapeL;     //xy=2848,800
    AudioEffectWaveshaper    waveshapeR;     //xy=2849,1040
    AudioMixer4              waveshapeMixerL; //xy=3065,780
    AudioMixer4              waveshapeMixerR; //xy=3066,1020
    AudioMixer4              ampLfoMixer;    //xy=3069,520
    AudioEffectMultiply      lfoAmpL;        //xy=3294,780
    AudioEffectMultiply      lfoAmpR;        //xy=3295,1020
    AudioSynthWaveformDc     noteVelocity;   //xy=3323,520
    AudioEffectMultiply      velocityAmpL;   //xy=3490,780
    AudioEffectMultiply      velocityAmpR;   //xy=3491,1020
    // AudioOutputI2S           i2s1;           //xy=3630,900

    AudioConnection          patchCord1 = AudioConnection(dc1Ref, env1);
    AudioConnection          patchCord2 = AudioConnection(dc1Ref, env2);
    AudioConnection          patchCord3 = AudioConnection(dc1Ref, 0, ampLfoMixer, 0);
    AudioConnection          patchCord4 = AudioConnection(osc1Shape, 0, osc1ShapeMixer, 0);
    AudioConnection          patchCord5 = AudioConnection(oscFmPhaseMod, 0, oscFmPhaseModMixer, 0);
    AudioConnection          patchCord6 = AudioConnection(envLfo, 0, osc1FreqMixer, 1);
    AudioConnection          patchCord7 = AudioConnection(envLfo, 0, osc1ShapeMixer, 1);
    AudioConnection          patchCord8 = AudioConnection(envLfo, 0, filter1FreqMixer, 1);
    AudioConnection          patchCord9 = AudioConnection(envLfo, 0, lfoFilter, 0);
    AudioConnection          patchCord10 = AudioConnection(env1, 0, env1Exp, 0);
    AudioConnection          patchCord11 = AudioConnection(env1, 0, env1Exp, 1);
    AudioConnection          patchCord12 = AudioConnection(env2, 0, osc1FreqMixer, 3);
    AudioConnection          patchCord13 = AudioConnection(env2, 0, osc1ShapeMixer, 3);
    AudioConnection          patchCord14 = AudioConnection(env2, 0, filter1FreqMixer, 3);
    AudioConnection          patchCord15 = AudioConnection(env2, 0, osc1WaveFoldMixer, 3);
    AudioConnection          patchCord16 = AudioConnection(env2, 0, oscFmPhaseModMixer, 3);
    AudioConnection          patchCord17 = AudioConnection(env1Exp, 0, env1AmpL, 0);
    AudioConnection          patchCord18 = AudioConnection(env1Exp, 0, env1AmpR, 0);
    AudioConnection          patchCord19 = AudioConnection(osc1FreqMixer, 0, osc1, 0);
    AudioConnection          patchCord20 = AudioConnection(osc1FreqMixer, 0, osc1Unison2, 0);
    AudioConnection          patchCord21 = AudioConnection(osc1FreqMixer, 0, osc1Unison3, 0);
    AudioConnection          patchCord22 = AudioConnection(osc1FreqMixer, 0, osc1Unison4, 0);
    AudioConnection          patchCord23 = AudioConnection(osc1FreqMixer, 0, osc1Unison5, 0);
    AudioConnection          patchCord24 = AudioConnection(osc1FreqMixer, 0, osc1Unison1, 0);
    AudioConnection          patchCord25 = AudioConnection(osc1FreqMixer, 0, osc1Unison6, 0);
    AudioConnection          patchCord26 = AudioConnection(osc1ShapeMixer, 0, osc1, 1);
    AudioConnection          patchCord27 = AudioConnection(osc1ShapeMixer, 0, osc1Unison2, 1);
    AudioConnection          patchCord28 = AudioConnection(osc1ShapeMixer, 0, osc1Unison3, 1);
    AudioConnection          patchCord29 = AudioConnection(osc1ShapeMixer, 0, osc1Unison4, 1);
    AudioConnection          patchCord30 = AudioConnection(osc1ShapeMixer, 0, osc1Unison5, 1);
    AudioConnection          patchCord31 = AudioConnection(osc1ShapeMixer, 0, osc1Unison1, 1);
    AudioConnection          patchCord32 = AudioConnection(osc1ShapeMixer, 0, osc1Unison6, 1);
    AudioConnection          patchCord33 = AudioConnection(oscFmPhaseModMixer, 0, oscFmEnv2Mod, 1);
    AudioConnection          patchCord34 = AudioConnection(osc1, 0, osc1WaveFolder, 1);
    AudioConnection          patchCord35 = AudioConnection(oscFm, 0, oscMixerL, 2);
    AudioConnection          patchCord36 = AudioConnection(oscFm, 0, oscMixerR, 2);
    AudioConnection          patchCord37 = AudioConnection(osc1Unison1, 0, osc1UnisonMixerR, 0);
    AudioConnection          patchCord38 = AudioConnection(osc1Unison2, 0, osc1UnisonMixerL, 0);
    AudioConnection          patchCord39 = AudioConnection(osc1Unison3, 0, osc1UnisonMixerR, 1);
    AudioConnection          patchCord40 = AudioConnection(osc1Unison4, 0, osc1UnisonMixerL, 1);
    AudioConnection          patchCord41 = AudioConnection(osc1Unison5, 0, osc1UnisonMixerR, 2);
    AudioConnection          patchCord42 = AudioConnection(osc1Unison6, 0, osc1UnisonMixerL, 2);
    AudioConnection          patchCord43 = AudioConnection(oscFmEnv2Mod, 0, oscFm, 0);
    AudioConnection          patchCord44 = AudioConnection(osc1WaveFold, 0, osc1WaveFoldMixer, 0);
    AudioConnection          patchCord45 = AudioConnection(osc1UnisonMixerL, 0, oscMixerL, 1);
    AudioConnection          patchCord46 = AudioConnection(osc1WaveFoldMixer, 0, osc1WaveFolder, 0);
    AudioConnection          patchCord47 = AudioConnection(osc1UnisonMixerR, 0, oscMixerR, 1);
    AudioConnection          patchCord48 = AudioConnection(kbdTrack, 0, filter1FreqSubMixer, 1);
    AudioConnection          patchCord49 = AudioConnection(filter1Freq, 0, filter1FreqSubMixer, 0);
    AudioConnection          patchCord50 = AudioConnection(kbdVelocity, 0, filter1FreqSubMixer, 2);
    AudioConnection          patchCord51 = AudioConnection(osc1WaveFolder, 0, oscMixerL, 0);
    AudioConnection          patchCord52 = AudioConnection(osc1WaveFolder, 0, oscFmEnv2Mod, 0);
    AudioConnection          patchCord53 = AudioConnection(osc1WaveFolder, 0, oscMixerR, 0);
    AudioConnection          patchCord54 = AudioConnection(filter1FreqMixer, 0, filter1L, 1);
    AudioConnection          patchCord55 = AudioConnection(filter1FreqMixer, 0, filter2FreqMixer, 2);
    AudioConnection          patchCord56 = AudioConnection(filter1FreqMixer, 0, filter1R, 1);
    AudioConnection          patchCord57 = AudioConnection(filter1FreqSubMixer, 0, filter1FreqMixer, 0);
    AudioConnection          patchCord58 = AudioConnection(oscMixerL, filterPreAmpL);
    AudioConnection          patchCord59 = AudioConnection(oscMixerR, filterPreAmpR);
    AudioConnection          patchCord60 = AudioConnection(filter2FreqOffset, 0, filter2FreqMixer, 0);
    AudioConnection          patchCord61 = AudioConnection(filterPreAmpL, 0, filter2L, 0);
    AudioConnection          patchCord62 = AudioConnection(filterPreAmpL, 0, filterMixer2L, 0);
    AudioConnection          patchCord63 = AudioConnection(filterPreAmpR, 0, filter2R, 0);
    AudioConnection          patchCord64 = AudioConnection(filterPreAmpR, 0, filterMixer2R, 0);
    AudioConnection          patchCord65 = AudioConnection(filter2FreqMixer, 0, filter2L, 1);
    AudioConnection          patchCord66 = AudioConnection(filter2FreqMixer, 0, filter2R, 1);
    AudioConnection          patchCord67 = AudioConnection(filter2L, 0, filterMixer2L, 1);
    AudioConnection          patchCord68 = AudioConnection(filter2L, 2, filterMixer2L, 3);
    AudioConnection          patchCord69 = AudioConnection(filter2R, 0, filterMixer2R, 1);
    AudioConnection          patchCord70 = AudioConnection(filter2R, 2, filterMixer2R, 3);
    AudioConnection          patchCord71 = AudioConnection(filterMixer2L, 0, filter1L, 0);
    AudioConnection          patchCord72 = AudioConnection(filterMixer2L, 0, filterMixer1L, 0);
    AudioConnection          patchCord73 = AudioConnection(filterMixer2R, 0, filter1R, 0);
    AudioConnection          patchCord74 = AudioConnection(filterMixer2R, 0, filterMixer1R, 0);
    AudioConnection          patchCord75 = AudioConnection(filter1L, 0, filterMixer1L, 1);
    AudioConnection          patchCord76 = AudioConnection(filter1L, 2, filterMixer1L, 3);
    AudioConnection          patchCord77 = AudioConnection(filter1R, 0, filterMixer1R, 1);
    AudioConnection          patchCord78 = AudioConnection(filter1R, 2, filterMixer1R, 3);
    AudioConnection          patchCord79 = AudioConnection(filterMixer1L, 0, env1AmpL, 1);
    AudioConnection          patchCord80 = AudioConnection(filterMixer1R, 0, env1AmpR, 1);
    AudioConnection          patchCord81 = AudioConnection(env1AmpL, 0, waveshapeMixerL, 0);
    AudioConnection          patchCord82 = AudioConnection(env1AmpL, waveshapeL);
    AudioConnection          patchCord83 = AudioConnection(env1AmpR, 0, waveshapeMixerR, 0);
    AudioConnection          patchCord84 = AudioConnection(env1AmpR, waveshapeR);
    AudioConnection          patchCord85 = AudioConnection(lfoFilter, 0, ampLfoMixer, 1);
    AudioConnection          patchCord86 = AudioConnection(waveshapeL, 0, waveshapeMixerL, 1);
    AudioConnection          patchCord87 = AudioConnection(waveshapeR, 0, waveshapeMixerR, 1);
    AudioConnection          patchCord88 = AudioConnection(waveshapeMixerL, 0, lfoAmpL, 1);
    AudioConnection          patchCord89 = AudioConnection(waveshapeMixerR, 0, lfoAmpR, 1);
    AudioConnection          patchCord90 = AudioConnection(ampLfoMixer, 0, lfoAmpL, 0);
    AudioConnection          patchCord91 = AudioConnection(ampLfoMixer, 0, lfoAmpR, 0);
    AudioConnection          patchCord92 = AudioConnection(lfoAmpL, 0, velocityAmpL, 1);
    AudioConnection          patchCord93 = AudioConnection(lfoAmpR, 0, velocityAmpR, 1);
    AudioConnection          patchCord94 = AudioConnection(noteVelocity, 0, velocityAmpL, 0);
    AudioConnection          patchCord95 = AudioConnection(noteVelocity, 0, velocityAmpR, 0);
    // AudioConnection          patchCord96 = AudioConnection(velocityAmpL, 0, i2s1, 0);
    // AudioConnection          patchCord97 = AudioConnection(velocityAmpR, 0, i2s1, 1);

    // GUItool: end automatically generated code

    // patch cord to connect to the LFO provided by Synth, will be connected in initialize()
    AudioConnection          lfoInput;

    // patch cords to connect to the voice mixers provided by Synth, will be connected in initialize()
    AudioConnection          outputL;
    AudioConnection          outputR;

    // 450hz with + and - 5 octaves gives a range of 14.0625 to 14400hz, which is just below the maximum of AudioFilterStateVariable (around 14.5khz)
    static constexpr float FILTER_FREQUENCY{450.0f};
    static constexpr float FILTER_OCTAVE_CONTROL{5.0f};

    // in a note on?
    bool currentMidiNoteOn{false};
    // which note is currently playing
    uint8_t currentMidiNote{0};
    // is the voice in (pedal) sustain?
    bool currentSustain{false};

    // timestamp last note on
    uint32_t lastNoteOn{0L};
    // timestamp last note off
    uint32_t lastNoteOff{0L};

    // current values
    uint8_t currentPitchChangeRange{0};
    float currentPitchChangeValue{0.0f};
    float currentModWhlValue{0.0f};
    float currentOsc1Volume{1.0f};
    float currentOscFmVolume{0.0f};
    float currentOsc1UnisonMixCenter{1.0f};
    uint8_t currentOsc1SynthWaveform{0};
    uint8_t currentOscFmSynthWaveform{0};
    int8_t currentOsc1Octave{0};
    int8_t currentOscFmOctave{0};
    int8_t currentOsc1Transpose{0};
    int8_t currentOscFmTranspose{0};
    float currentOsc1Detune{0.0f};
    float currentOscFmDetune{0.0f};
    float currentOsc1FrequencyMultiplier{1.0f};
    float currentOscFmFrequencyMultiplier{1.0f};

    float currentFilter1FreqValue{0.0f};
    float currentFilter1FreqModEnv2Offset{0.0f};

    float currentEnvReverseLevel{0.0f};
    float currentEnv1Attack{0.0f};
    float currentEnv1Release{0.0f};
    float currentEnv2Attack{0.0f};
    float currentEnv2Release{0.0f};

    float currentAmpKbdVelocity{0.5f};

    // unison detune ratios for oscillator 1

    // see: https://www.kvraudio.com/forum/viewtopic.php?t=258924&start=180
    // integer ratios
    // static constexpr float unisonDetune1Ratio{5.0f/256.0f};
    // static constexpr float unisonDetune2Ratio{16.0f/256.0f};
    // static constexpr float unisonDetune3Ratio{28.0f/256.0f};
    // static constexpr float unisonDetune4Ratio{-5.0f/256.0f};
    // static constexpr float unisonDetune5Ratio{-16.0f/256.0f};
    // static constexpr float unisonDetune6Ratio{-28.0f/256.0f};
    
    // russel
    // static constexpr float unisonDetune1Ratio{1.0f - 0.8930f};
    // static constexpr float unisonDetune2Ratio{1.0f - 0.9390f};
    // static constexpr float unisonDetune3Ratio{1.0f - 0.9800f};
    // static constexpr float unisonDetune4Ratio{1.0f - 1.0200f};
    // static constexpr float unisonDetune5Ratio{1.0f - 1.0640f};
    // static constexpr float unisonDetune6Ratio{1.0f - 1.1100f};
    
    // Szabo    
    // static constexpr float unisonDetune1Ratio{1.0f - 0.88997686f};
    // static constexpr float unisonDetune2Ratio{1.0f - 0.93711560f};
    // static constexpr float unisonDetune3Ratio{1.0f - 0.98047643f};
    // static constexpr float unisonDetune4Ratio{1.0f - 1.01991221f};
    // static constexpr float unisonDetune5Ratio{1.0f - 1.06216538f};
    // static constexpr float unisonDetune6Ratio{1.0f - 1.10745242f};
    
    // stepvhen    
    // static constexpr float unisonDetune1Ratio{1.0f - 0.89062500f};
    // static constexpr float unisonDetune2Ratio{1.0f - 0.93750000f};
    // static constexpr float unisonDetune3Ratio{1.0f - 0.98046875f};
    // static constexpr float unisonDetune4Ratio{1.0f - 1.01953125f};
    // static constexpr float unisonDetune5Ratio{1.0f - 1.06250000f};
    // static constexpr float unisonDetune6Ratio{1.0f - 1.10937500f};
    
    // https://www.kvraudio.com/forum/viewtopic.php?p=5413665#p5413665
    static constexpr float unisonDetune1Ratio{pow(2.0f, -191.0f/1200.0f) - 1.0f};
    static constexpr float unisonDetune2Ratio{pow(2.0f, -109.0f/1200.0f) - 1.0f};
    static constexpr float unisonDetune3Ratio{pow(2.0f, -37.0f/1200.0f) - 1.0f};
    static constexpr float unisonDetune4Ratio{pow(2.0f, 31.0f/1200.0f) - 1.0f};
    static constexpr float unisonDetune5Ratio{pow(2.0f, 107.0f/1200.0f) - 1.0f};
    static constexpr float unisonDetune6Ratio{pow(2.0f, 181.0f/1200.0f) - 1.0f};

    // unison detune level
    float unisonDetune{0.0f};

    /**
     * Convert a MIDI note to a keyboard tracking value using FILTER_FREQUENCY and FILTER_OCTAVE_CONTROL.
     * 
     * @param note note
     * @return float keyboard tracking value
     */
    static float midiNoteToKbdTrack(uint8_t note)
    {
        return constrain(log2(MIDI_NOTE_FREQ[note] / FILTER_FREQUENCY) / FILTER_OCTAVE_CONTROL, -1.0f, 1.0f);
    }

    /**
     * Convert a MIDI velocity to amplitude.
     * 
     * @param velocity velocity
     * @return float amplitude
     */
    float midiVelocityToAmplitude(uint8_t velocity) const
    {
        return PARAM_SCALE_POWER[map(velocity, 0, 127, 127 - round(127.0f * currentAmpKbdVelocity), 127)];
    }

    /**
     * Restart all oscillator waveforms.
     * 
     * Use AudioNoInterrupts() before and AudioInterrupts() after calling this method.
     */
    void restartOscWaveForms()
    {
        // osc 1 + unison voices
        auto osc1SynthWaveform = getSynthWaveformByValue(currentOsc1SynthWaveform);
        if (osc1SynthWaveform.audioWaveform == WAVEFORM_ARBITRARY)
        {
            // sampled waveform selected, load the waveform in the buffer
            osc1.arbitraryWaveform(osc1SynthWaveform.waveFormArray, 44100);
            osc1Unison1.arbitraryWaveform(osc1SynthWaveform.waveFormArray, 44100);
            osc1Unison2.arbitraryWaveform(osc1SynthWaveform.waveFormArray, 44100);
            osc1Unison3.arbitraryWaveform(osc1SynthWaveform.waveFormArray, 44100);
            osc1Unison4.arbitraryWaveform(osc1SynthWaveform.waveFormArray, 44100);
            osc1Unison5.arbitraryWaveform(osc1SynthWaveform.waveFormArray, 44100);
            osc1Unison6.arbitraryWaveform(osc1SynthWaveform.waveFormArray, 44100);
        }
        osc1.begin(osc1SynthWaveform.audioWaveform);
        osc1Unison1.begin(osc1SynthWaveform.audioWaveform);
        osc1Unison2.begin(osc1SynthWaveform.audioWaveform);
        osc1Unison3.begin(osc1SynthWaveform.audioWaveform);
        osc1Unison4.begin(osc1SynthWaveform.audioWaveform);
        osc1Unison5.begin(osc1SynthWaveform.audioWaveform);
        osc1Unison6.begin(osc1SynthWaveform.audioWaveform);

        // osc fm
        auto oscFmSynthWaveform = getSynthWaveformByValue(currentOscFmSynthWaveform);
        if (oscFmSynthWaveform.audioWaveform == WAVEFORM_ARBITRARY)
        {
            oscFm.arbitraryWaveform(oscFmSynthWaveform.waveFormArray, 44100);
        }
        oscFm.begin(oscFmSynthWaveform.audioWaveform);

        // restart the phase of the oscillators
        // these calls require a modification to the Teensy Audio library, see Code.md for more information
        // the unison oscillators are not restarted, they are supposed to be out of phase
        #ifndef DISABLE_OSC_RESTART
        osc1.restart();
        oscFm.restart();
        #endif
    }

    /**
     * Update the frequency of osc 1 and unison voices based on the current MIDI note, pitch change and other related current values.
     */
    void updateOsc1Frequency()
    {
        currentOsc1FrequencyMultiplier = pow(2.0f, float(currentOsc1Octave)) * pow(2.0f, currentOsc1Transpose / 12.0f) * pow(2.0f, (currentPitchChangeRange * currentPitchChangeValue) / 12.0f) * pow(2.0f, currentOsc1Detune / 1200.0f);
        float centerFrequency = MIDI_NOTE_FREQ[currentMidiNote] * currentOsc1FrequencyMultiplier;
        
        // Serial.print("osc 1 freq: ");
        // Serial.println(centerFrequency);

        osc1.frequency(centerFrequency);
        osc1Unison1.frequency(centerFrequency * (1.0f + unisonDetune1Ratio * unisonDetune));
        osc1Unison2.frequency(centerFrequency * (1.0f + unisonDetune2Ratio * unisonDetune));
        osc1Unison3.frequency(centerFrequency * (1.0f + unisonDetune3Ratio * unisonDetune));
        osc1Unison4.frequency(centerFrequency * (1.0f + unisonDetune4Ratio * unisonDetune));
        osc1Unison5.frequency(centerFrequency * (1.0f + unisonDetune5Ratio * unisonDetune));
        osc1Unison6.frequency(centerFrequency * (1.0f + unisonDetune6Ratio * unisonDetune));
    }

    /**
     * Update the frequency of osc fm based on the current MIDI note, pitch change and other related current values.
     */
    void updateOscFmFrequency()
    {
        currentOscFmFrequencyMultiplier = pow(2.0f, float(currentOscFmOctave)) * pow(2.0f, currentOscFmTranspose / 12.0f) * pow(2.0f, (currentPitchChangeRange * currentPitchChangeValue) / 12.0f) * pow(2.0f, currentOscFmDetune / 1200.0f);
        float centerFrequency = MIDI_NOTE_FREQ[currentMidiNote] * currentOscFmFrequencyMultiplier;

        // Serial.print("osc 2 freq: ");
        // Serial.println(centerFrequency);

        oscFm.frequency(centerFrequency);
    }

    /**
     * Update the frequency of filter 1 based on current values.
     */
    void updateFilter1Freq()
    {
        // currentFilter1FreqValue ranges from -2 to +6 oct
        filter1Freq.amplitude(constrain((currentFilter1FreqValue + 0.5f) * (4.0f / FILTER_OCTAVE_CONTROL)  + currentFilter1FreqModEnv2Offset, -1.0f, 1.0f));
    }

    /**
     * Update the osc mixers using the current values.
     */
    void updateOscMixer()
    {
        oscMixerL.gain(0, currentOsc1Volume * currentOsc1UnisonMixCenter);
        oscMixerL.gain(1, currentOsc1Volume);
        oscMixerL.gain(2, currentOscFmVolume);
        oscMixerR.gain(0, currentOsc1Volume * currentOsc1UnisonMixCenter);
        oscMixerR.gain(1, currentOsc1Volume);
        oscMixerR.gain(2, currentOscFmVolume);
    }

    /**
     * Update the attack and release of ENV1 with current modulation values.
     */
    void updateEnv1AttackRelease()
    {
        auto modValue = currentModWhlValue * currentEnvReverseLevel;
        env1.attack(currentEnv1Attack * (1.0f - modValue) + currentEnv1Release * modValue);
        env1.release(currentEnv1Release * (1.0f - modValue) + currentEnv1Attack * modValue);
    }

    /**
     * Update the attack and release of ENV2 with current modulation values.
     */
    void updateEnv2AttackRelease()
    {
        auto modValue = currentModWhlValue * currentEnvReverseLevel;
        env2.attack(currentEnv2Attack * (1.0f - modValue) + currentEnv2Release * modValue);
        env2.release(currentEnv2Release * (1.0f - modValue) + currentEnv2Attack * modValue);
    }

public:
    /**
     * Initialize the SynthVoice.
     * 
     * @param destinationL audio object to connect the left output of this synth voice to
     * @param destinationInputL input number of the audio object to connect the left output of this synth voice to
     * @param destinationR audio object to connect the right output of this synth voice to
     * @param destinationInputR input number of the audio object to connect the right output of this synth voice to
     * @param lfo audio object to connect the LFO input of this synth voice to
     * @param lfoOutput output number of the audio object to connect the LFO input of this synth voice to
     */
    void initialize(AudioStream &destinationL, unsigned char destinationInputL, AudioStream &destinationR, unsigned char destinationInputR, AudioStream &lfo, unsigned char lfoOutput)
    {
        // connect the audio output of this synth voice to the voice mixer of Synth
        outputL.connect(velocityAmpL, 0, destinationL, destinationInputL);
        outputR.connect(velocityAmpR, 0, destinationR, destinationInputR);

        // connect the output of the LFO provided by Synth
        lfoInput.connect(lfo, lfoOutput, envLfo, 0);

        // initialize some audio objects with initial or fixed values
        AudioNoInterrupts();

        dc1Ref.amplitude(1.0f);

        lfoFilter.frequency(250.0f);

        osc1.amplitude(1.0f);
        osc1Unison1.amplitude(1.0f);
        osc1Unison2.amplitude(1.0f);
        osc1Unison3.amplitude(1.0f);
        osc1Unison4.amplitude(1.0f);
        osc1Unison5.amplitude(1.0f);
        osc1Unison6.amplitude(1.0f);

        oscFm.amplitude(1.0f);

        osc1WaveFold.amplitude(0.5f);

        osc1.frequencyModulation(4.0f);
        osc1Unison1.frequencyModulation(4.0f);
        osc1Unison2.frequencyModulation(4.0f);
        osc1Unison3.frequencyModulation(4.0f);
        osc1Unison4.frequencyModulation(4.0f);
        osc1Unison5.frequencyModulation(4.0f);
        osc1Unison6.frequencyModulation(4.0f);

        osc1FreqMixer.gain(0, 1.0f);

        osc1ShapeMixer.gain(0, 1.0f);

        osc1WaveFoldMixer.gain(0, 1.0f);

        oscFm.frequencyModulation(0.0f);
        oscFm.phaseModulation(720.0f);


        filter1L.frequency(FILTER_FREQUENCY);
        filter1R.frequency(FILTER_FREQUENCY);
        filter1L.octaveControl(FILTER_OCTAVE_CONTROL);
        filter1R.octaveControl(FILTER_OCTAVE_CONTROL);

        filter2L.frequency(FILTER_FREQUENCY);
        filter2R.frequency(FILTER_FREQUENCY);
        filter2L.octaveControl(FILTER_OCTAVE_CONTROL);
        filter2R.octaveControl(FILTER_OCTAVE_CONTROL);

        envLfo.attack(0.0f);
        envLfo.decay(12000.0f);
        envLfo.sustain(1.0f);
        envLfo.release(12000.0f);

        env1.releaseNoteOn(1.0f);
        env2.releaseNoteOn(1.0f);

        AudioInterrupts();
    }

    /**
     * Get a synth waveform by number.
     * 
     * @param value waveform number
     * @return SynthWaveform synth waveform
     */
    static SynthWaveform getSynthWaveformByValue(uint8_t value)
    {
        if (value >= SYNTH_WAVEFORMS.size())
        {
            value = (uint8_t)SYNTH_WAVEFORMS.size() - 1;
        }
        return SYNTH_WAVEFORMS.at(value);
    }

    /**
     * Note on handler.
     * 
     * @param note note
     * @param velocity velocity
     */
    void onNoteOn(uint8_t note, uint8_t velocity)
    {
        currentMidiNote = note;
        currentMidiNoteOn = true;
        lastNoteOn = millis();

        AudioNoInterrupts();

        // kbdTrack needs to be adjusted at least 1 ms before the note starts to prevent ticks
        kbdTrack.amplitude(midiNoteToKbdTrack(note), 0);

        updateFilter1Freq();
        kbdVelocity.amplitude((velocity / 63.5f) - 1.0f, 1);

        // fade the last note in this voice while we wait for kbdTrack to adjust
        noteVelocity.amplitude(0.0f, 1);
        env1.noteOff();
        env2.noteOff();
        envLfo.noteOff();

        AudioInterrupts();

        delay(1);

        AudioNoInterrupts();

        updateOsc1Frequency();
        updateOscFmFrequency();

        restartOscWaveForms();
        noteVelocity.amplitude(midiVelocityToAmplitude(velocity));
        env1.noteOn();
        env2.noteOn();
        envLfo.noteOn();

        AudioInterrupts();
    }

    /**
     * Note off handler.
     * 
     * @param note note
     */
    void onNoteOff(uint8_t note)
    {
        if (note != currentMidiNote)
        {
            return;
        }

        // trigger envelop note off only if the sustain pedal is not pressed
        if (!currentSustain)
        {
            AudioNoInterrupts();
            env1.noteOff();
            env2.noteOff();
            envLfo.noteOff();
            AudioInterrupts();
        }

        currentMidiNoteOn = false;
        lastNoteOff = millis();
    }

    /**
     * Sustain toggle handler.
     * 
     * @param on true if sustain is on
     */
    void onSustainToggle(bool on)
    {
        if (!on && !currentMidiNoteOn && currentSustain)
        {
            // turn the note off if sustain toggles to off and the voice is currently in sustain and not in note on
            currentSustain = on;
            onNoteOff(currentMidiNote);
        }
        else
        {
            currentSustain = on;
        }
    }

    /**
     * Get the current MIDI note.
     * 
     * @return uint8_t note
     */
    uint8_t getCurrentMidiNote()
    {
        return currentMidiNote;
    }

    /**
     * Get the current MIDI note on state.
     * 
     * @return bool true if on
     */
    bool getCurrentMidiNoteOn()
    {
        return currentMidiNoteOn;
    }

    /**
     * Get the timestamp of the last note on.
     * 
     * @return uint32_t timestamp
     */
    uint32_t getLastNoteOn()
    {
        return lastNoteOn;
    }

    /**
     * Get the timestamp of the last note off.
     * 
     * @return uint32_t timestamp
     */
    uint32_t getLastNoteOff()
    {
        return lastNoteOff;
    }

    /**
     * Set the pitch bend range.
     * 
     * @param value range in semitones
     */
    void setPitchChangeRange(uint8_t value)
    {
        currentPitchChangeRange = value;
        updateOsc1Frequency();
        updateOscFmFrequency();
    }

    /**
     * Set the current pitch bend.
     * @param value pitch change (-1.0f - 1.0f)
     */
    void setPitchChange(float value)
    {
        currentPitchChangeValue = value;
        updateOsc1Frequency();
        updateOscFmFrequency();
    }

    /**
     * Set the current modulation wheel value.
     * @param value modulation (0.0f - 1.0f)
     */
    void setModWhl(float value)
    {
        currentModWhlValue = value;
        updateEnv1AttackRelease();
        updateEnv2AttackRelease();
    }

    /**
     * Log CPU / memory usage for debugging purposes.
     */
    void logCpuUsageStats()
    {
        Serial.println();

        Serial.print("osc1WaveFolder CPU usage: ");
        Serial.print(osc1WaveFolder.processorUsageMax());
        Serial.println("%");

        Serial.print("waveshapeL CPU usage: ");
        Serial.print(waveshapeL.processorUsageMax());
        Serial.println("%");

        Serial.print("osc1 CPU usage: ");
        Serial.print(osc1.processorUsageMax());
        Serial.println("%");

        Serial.print("oscFm CPU usage: ");
        Serial.print(oscFm.processorUsageMax());
        Serial.println("%");

        Serial.print("filter1L CPU usage: ");
        Serial.print(filter1L.processorUsageMax());
        Serial.println("%");

        Serial.print("filter2L CPU usage: ");
        Serial.print(filter2L.processorUsageMax());
        Serial.println("%");

        Serial.print("Total audio CPU usage: ");
        Serial.print(AudioProcessorUsageMax());
        Serial.println("%");

        Serial.print("Total audio memory usage: ");
        Serial.print(AudioMemoryUsageMax());
        Serial.println();

        osc1WaveFolder.processorUsageMaxReset();
        waveshapeL.processorUsageMaxReset();
        osc1.processorUsageMaxReset();
        oscFm.processorUsageMaxReset();
        filter1L.processorUsageMaxReset();
        filter2L.processorUsageMaxReset();
        AudioProcessorUsageMaxReset();
        AudioMemoryUsageMaxReset();
    }

    /**
     * Set the env 1 attack time.
     * 
     * @param value attack time in milliseconds
     */
    void setEnv1Attack(float value)
    {
        currentEnv1Attack = value;
        updateEnv1AttackRelease();
    }

    /**
     * Set the env 1 decay time.
     * 
     * @param value decay time in milliseconds
     */
    void setEnv1Decay(float value)
    {
        env1.decay(value);
    }

    /**
     * Set the env 1 sustain level.
     * 
     * @param value sustain level (0.0f - 1.0f)
     */
    void setEnv1Sustain(float value)
    {
        // use a square root to compensate the sustain level for the power 2 connected to the output of env 1
        env1.sustain(sqrt(value));
    }

    /**
     * Set the env 1 release time.
     * 
     * @param value release time in milliseconds
     */
    void setEnv1Release(float value)
    {
        currentEnv1Release = value;
        updateEnv1AttackRelease();
    }

    /**
     * Set the env 2 attack time.
     * 
     * @param value attack time in milliseconds
     */
    void setEnv2Attack(float value)
    {
        currentEnv2Attack = value;
        updateEnv2AttackRelease();
    }

    /**
     * Set the env 2 decay time.
     * @param value decay time in milliseconds
     */
    void setEnv2Decay(float value)
    {
        env2.decay(value);
    }

    /**
     * Set the env 2 sustain level.
     * @param value sustain level (0.0f - 1.0f)
     */
    void setEnv2Sustain(float value)
    {
        env2.sustain(value);
    }

    /**
     * Set the env 2 release time.
     * @param value release time in milliseconds
     */
    void setEnv2Release(float value)
    {
        currentEnv2Release = value;
        updateEnv2AttackRelease();
    }

    /**
     * Set the frequency of filter 1 (relative to the current MIDI note and keyboard tracking level).
     * 
     * @param value value (-1.0f - 1.0f)
     */
    void setFilter1Frequency(float value)
    {
        currentFilter1FreqValue = value;
        updateFilter1Freq();
    }

    /**
     * Set the resonance level of filter 1.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setFilter1Resonance(float value)
    {
        // reduce the the pre-filter gain to prevent clipping cause by the gain around the resonance peak
        auto gain = 0.85f * pow(0.05f, value) + 0.15f;
        filterPreAmpL.gain(gain);
        filterPreAmpR.gain(gain);

        // map the resonance to 0.7f - 5.0f required by AudioFilterStateVariable
        auto resonance = map(value, 0.0f, 1.0f, 0.7f, 5.0f);
        filter1L.resonance(resonance);
        filter1R.resonance(resonance);
    }

    /**
     * Set the keyboard tracking level of filter 1.
     * 
     * @param value level (0.0f to 1.0f, 1.0f is 100% of the note frequency)
     */
    void setFilter1KbdTrack(float value)
    {
        filter1FreqSubMixer.gain(1, value);
    }

    /**
     * Set the level of filter 1 frequency modulation using the keyboard velocity.
     * 
     * @param value level (-1.0f - 1.0f)
     */
    void setFilter1KbdVelocity(float value)
    {
        filter1FreqSubMixer.gain(2, value);
    }

    /**
     * Set the level of filter 1 frequency modulation using env 2.
     * 
     * @param value level (-1.0f - 1.0f)
     */
    void setFilter1Env2(float value)
    {
        AudioNoInterrupts();
        filter1FreqMixer.gain(3, value);
        currentFilter1FreqModEnv2Offset = value / -2.0f;
        updateFilter1Freq();
        AudioInterrupts();
    }

    /**
     * Set the level of filter 1 frequency modulation using the lfo.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setFilter1Lfo(float value)
    {
        filter1FreqMixer.gain(1, value);
    }

    /**
     * Set the filter mode.
     * 
     * @param value filter mode
     */
    void setFilterMode(uint8_t value)
    {
        // 0: "1:LPF12 & 2:LPF12"
        // 1: "1:LPF12 & 2:HPF12"
        // 2: "1:HPF12 & 2:LPF12"
        // 3: "1:HPF12 & 2:HPF12"
        // 4: "1:LPF12"
        // 5: "1:HPF12"
        // 6: "Bypass"

        // input 0: bypass
        // input 1: low-pass
        // input 3: high-pass

        filterMixer1L.gain(0, value == 6 ? 1.0f : 0.0f);
        filterMixer1R.gain(0, value == 6 ? 1.0f : 0.0f);

        filterMixer1L.gain(1, value == 0 || value == 1 || value == 4 ? 1.0f : 0.0f);
        filterMixer1R.gain(1, value == 0 || value == 1 || value == 4 ? 1.0f : 0.0f);

        filterMixer1L.gain(2, 0.0f);
        filterMixer1R.gain(2, 0.0f);

        filterMixer1L.gain(3, value == 2 || value == 3 || value == 5 ? 1.0f : 0.0f);
        filterMixer1R.gain(3, value == 2 || value == 3 || value == 5 ? 1.0f : 0.0f);

        filterMixer2L.gain(0, value == 4 || value == 5 || value == 6 ? 1.0f : 0.0f);
        filterMixer2R.gain(0, value == 4 || value == 5 || value == 6 ? 1.0f : 0.0f);

        filterMixer2L.gain(1, value == 0 || value == 2 ? 1.0f : 0.0f);
        filterMixer2R.gain(1, value == 0 || value == 2 ? 1.0f : 0.0f);

        filterMixer2L.gain(2, 0.0f);
        filterMixer2R.gain(2, 0.0f);

        filterMixer2L.gain(3, value == 1 || value == 3 ? 1.0f : 0.0f);
        filterMixer2R.gain(3, value == 1 || value == 3 ? 1.0f : 0.0f);
    }

    /**
     * Set the filter 2 frequency offset relative to filter 1.
     * 
     * @param value offset (-1.0f - 1.0f)
     */
    void setFilter2FrequencyOffset(float value)
    {
        filter2FreqOffset.amplitude(value, TRANSITION_SPEED_MS);
    }

    /**
     * Set the LFO envelope attack time.
     * 
     * @param value attack time in milliseconds
     */
    void setEnvLfoAttack(float value)
    {
        envLfo.attack(value);
    }

    /**
     * Set the osc 1 / fm volume mix.
     * 
     * @param value 0.0f = 100% osc 1 and 0% osc fm, 1.0f = 0% osc 1 and 100% osc fm
     */
    void setOscVolumeMix(float value)
    {
        currentOsc1Volume = 1.0f - value;
        currentOscFmVolume = value;
        updateOscMixer();
    }

    /**
     * Set the osc 1 synth waveform.
     * 
     * @param value synth waveform number
     */
    void setOsc1SynthWaveform(uint8_t value)
    {
        currentOsc1SynthWaveform = value;
        AudioNoInterrupts();
        restartOscWaveForms();
        AudioInterrupts();
    }

    /**
     * Set the osc fm synth waveform.
     * 
     * @param value synth waveform number
     */
    void setOscFmSynthWaveform(uint8_t value)
    {
        currentOscFmSynthWaveform = value;
        AudioNoInterrupts();
        restartOscWaveForms();
        AudioInterrupts();
    }

    /**
     * Set the osc 1 wavefold level.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setOsc1WaveFold(float value)
    {
        // 6,25% equals to 100% gain, above 6.25% wavefolding starts to happen
        osc1WaveFold.amplitude(map(value, 0.0f, 1.0f, 0.0625f, 1.0f), TRANSITION_SPEED_MS);
    }

    /**
     * Set the shape (for some of the synth waveforms) of osc 1.
     * 
     * @param value shape (0.0f - 1.0f, 0.5f is "normal" shape)
     */
    void setOsc1Shape(float value)
    {
        osc1Shape.amplitude(value, TRANSITION_SPEED_MS);
    }

    /**
     * Set the octave of osc fm (relative to the MIDI note frequency).
     * 
     * @param value octave (plus or minus)
     */
    void setOscFmOctave(int8_t value)
    {
        currentOscFmOctave = value;
        updateOscFmFrequency();
    }

    /**
     * Set the transpose of osc 1.
     * 
     * @param value transpose in semitones (plus or minus)
     */
    void setOsc1Transpose(int8_t value)
    {
        currentOsc1Transpose = value;
        updateOsc1Frequency();
    }
    /**
     * Set the transpose of osc fm.
     * 
     * @param value transpose in semitones (plus or minus)
     */
    void setOscFmTranspose(int8_t value)
    {
        currentOscFmTranspose = value;
        updateOscFmFrequency();
    }

    /**
     * Set the detune of osc 1.
     * 
     * @param value detune in cents (-50.0f - 50.0f)
     */
    void setOsc1Detune(float value)
    {
        currentOsc1Detune = value;
        updateOsc1Frequency();
    }

    /**
     * Set the detune of osc fm.
     * 
     * @param value detune in cents (-50.0f - 50.0f)
     */
    void setOscFmDetune(float value)
    {
        currentOscFmDetune = value;
        updateOscFmFrequency();
    }

    /**
     * Set the level of osc 1 frequency modulation using env 2.
     * 
     * @param value level (-1.0f - 1.0f)
     */
    void setOsc1ModFreqEnv2(float value)
    {
        osc1FreqMixer.gain(3, value / 4.0f);
    }

    /**
     * Set the level of osc 1 frequency modulation using the lfo.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setOsc1ModFreqLfo(float value)
    {
        osc1FreqMixer.gain(1, value / 8.0f);
    }

    /**
     * Set the level of osc 1 shape modulation using env 2.
     * 
     * @param value level (-1.0f - 1.0f)
     */
    void setOsc1ModShapeEnv2(float value)
    {
        osc1ShapeMixer.gain(3, value);
    }

    /**
     * Set the level of osc 1 shape modulation using the lfo.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setOsc1ModShapeLfo(float value)
    {
        osc1ShapeMixer.gain(1, value);
    }

    /**
     * Set the level of osc 1 wavefold modulation using env 2.
     * 
     * @param value level (-1.0f - 1.0f)
     */
    void setOsc1ModWaveFoldEnv2(float value)
    {
        osc1WaveFoldMixer.gain(3, value);
    }

    /**
     * Set the osc 1 unison detune level.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setOsc1UnisonDetune(float value)
    {
        // unisonDetune = pow(value, 50.0f) * 0.5f + pow(value, 5.0f) * 0.3f + value * 0.2f;
        unisonDetune = pow(value, 9.0f) * 0.5f + pow(value, 3.0f) * 0.3f + value * 0.2f;
        updateOsc1Frequency();
    }

    /**
     * Set the osc 1 unison mix level.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setOsc1UnisonMix(float value)
    {
        // adjust the center gain to compensate for volume increase by adding extra oscillators
        float unisonMixCenter = 1.0f - 6.0f * value / 7.0f;
        float unisonMixSide = value / 7.0f;

        // update the center gain
        currentOsc1UnisonMixCenter = unisonMixCenter;
        updateOscMixer();

        // update the side gain
        osc1UnisonMixerL.gain(0, unisonMixSide);
        osc1UnisonMixerL.gain(1, unisonMixSide);
        osc1UnisonMixerL.gain(2, unisonMixSide);
        osc1UnisonMixerR.gain(0, unisonMixSide);
        osc1UnisonMixerR.gain(1, unisonMixSide);
        osc1UnisonMixerR.gain(2, unisonMixSide);
    }

    /**
     * Set the level of osc fm phase modulation using env 2.
     * 
     * @param value level (-1.0f - 1.0f)
     */
    void setOscFmModPhaseEnv2(float value)
    {
        oscFmPhaseModMixer.gain(3, value);
    }

    /**
     * Set the level of osc fm phase modulation.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setOscFmPhaseMod(float value)
    {
        oscFmPhaseMod.amplitude(value, TRANSITION_SPEED_MS);
    }

    /**
     * Set the waveshape level.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setWaveshapeLevel(float value, float waveshapeArray[], const uint16_t waveshapeArraySize)
    {
        // try to compensate for gain increase caused by the waveshaping
        auto cleanGain = 1.0f - pow(value, 0.6f);
        auto waveshapeGain = pow(value, 0.5f) / 2.5f;

        waveshapeMixerL.gain(0, cleanGain);
        waveshapeMixerR.gain(0, cleanGain);
        waveshapeMixerL.gain(1, waveshapeGain);
        waveshapeMixerR.gain(1, waveshapeGain);

        waveshapeL.shape(waveshapeArray, waveshapeArraySize);
        waveshapeR.shape(waveshapeArray, waveshapeArraySize);
    }

    /**
     * Set the level of amplitude modulation using the lfo (tremolo).
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setAmpModLfo(float value)
    {
        ampLfoMixer.gain(0, 1.0f - value / 2.0f);
        ampLfoMixer.gain(1, value / 2.0f);
    }

    /**
     * Set the level of amplitude modulation using keyboard velocity.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setAmpKbdVelocity(float value)
    {
        currentAmpKbdVelocity = value;
    }

    /**
     * Set the env reverse level.
     * 
     * @param value level (0.0f - 1.0f)
     */
    void setEnvReverse(float value)
    {
        currentEnvReverseLevel = value;
        updateEnv1AttackRelease();
    }

};

#endif