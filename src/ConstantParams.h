#ifndef ConstantParams_h
#define ConstantParams_h

#include <vector>

#include "Param.h"
#include "MiscUtil.h"

// list of parameters available for the synthesizer
const std::vector<Param> PARAMS{
    // envelope 1
    Param(
        PARAM_ID_ENV_1_ATTACK,
        PARAM_GROUP_NAME_ENV_1,
        "Attack",
        PARAM_MC_ENV_1_ATTACK,
        PARAM_CC_ENV_1_ATTACK,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnv1Attack(PARAM_SCALE_ENV_TIME[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.1fms", PARAM_SCALE_ENV_TIME[value]); }),
    Param(
        PARAM_ID_ENV_1_DECAY,
        PARAM_GROUP_NAME_ENV_1,
        "Decay",
        PARAM_MC_ENV_1_DECAY,
        PARAM_CC_ENV_1_DECAY,
        50,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnv1Decay(PARAM_SCALE_ENV_TIME[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.1fms", PARAM_SCALE_ENV_TIME[value]); }),
    Param(
        PARAM_ID_ENV_1_SUSTAIN,
        PARAM_GROUP_NAME_ENV_1,
        "Sustain",
        PARAM_MC_ENV_1_SUSTAIN,
        PARAM_CC_ENV_1_SUSTAIN,
        100,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnv1Sustain(PARAM_SCALE_POWER[value]); }),
    Param(
        PARAM_ID_ENV_1_RELEASE,
        PARAM_GROUP_NAME_ENV_1,
        "Release",
        PARAM_MC_ENV_1_RELEASE,
        PARAM_CC_ENV_1_RELEASE,
        50,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnv1Release(PARAM_SCALE_ENV_TIME[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.1fms", PARAM_SCALE_ENV_TIME[value]); }),

    // envelope 2
    Param(
        PARAM_ID_ENV_2_ATTACK,
        PARAM_GROUP_NAME_ENV_2,
        "Attack",
        PARAM_MC_ENV_2_ATTACK,
        PARAM_CC_ENV_2_ATTACK,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnv2Attack(PARAM_SCALE_ENV_TIME[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.1fms", PARAM_SCALE_ENV_TIME[value]); }),
    Param(
        PARAM_ID_ENV_2_DECAY,
        PARAM_GROUP_NAME_ENV_2,
        "Decay",
        PARAM_MC_ENV_2_DECAY,
        PARAM_CC_ENV_2_DECAY,
        50,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnv2Decay(PARAM_SCALE_ENV_TIME[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.1fms", PARAM_SCALE_ENV_TIME[value]); }),
    Param(
        PARAM_ID_ENV_2_SUSTAIN,
        PARAM_GROUP_NAME_ENV_2,
        "Sustain",
        PARAM_MC_ENV_2_SUSTAIN,
        PARAM_CC_ENV_2_SUSTAIN,
        100,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnv2Sustain(PARAM_SCALE_POWER[value]); }),
    Param(
        PARAM_ID_ENV_2_RELEASE,
        PARAM_GROUP_NAME_ENV_2,
        "Release",
        PARAM_MC_ENV_2_RELEASE,
        PARAM_CC_ENV_2_RELEASE,
        50,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnv2Release(PARAM_SCALE_ENV_TIME[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.1fms", PARAM_SCALE_ENV_TIME[value]); }),

    // filter1
    Param(
        PARAM_ID_FILTER_1_FREQ,
        PARAM_GROUP_NAME_FILTER,
        "Frequency",
        PARAM_MC_FILTER_1_FREQ,
        PARAM_CC_FILTER_1_FREQ,
        96,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setFilter1Frequency(PARAM_SCALE_LINEAR[value] * 2.0f - 1.0f); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.1f semitones", 96.0f * PARAM_SCALE_LINEAR[value] - 24.0f); }),
    Param(
        PARAM_ID_FILTER_1_RES,
        PARAM_GROUP_NAME_FILTER,
        "Resonance",
        PARAM_MC_FILTER_1_RES,
        PARAM_CC_FILTER_1_RES,
        40,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setFilter1Resonance(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),
    Param(
        PARAM_ID_FILTER_1_KBD_TRACK,
        PARAM_MI_FILTER_1_KBD_TRACK,
        PARAM_GROUP_NAME_FILTER,
        "Keyboard tracking",
        PARAM_MC_FILTER_1_KBD_TRACK,
        127,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setFilter1KbdTrack(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.0f%%%s", round(100 * PARAM_SCALE_LINEAR_CENTER_ZERO[value]), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),
    Param(
        PARAM_ID_FILTER_1_KBD_VELOCITY,
        PARAM_GROUP_NAME_FILTER_MOD,
        "Keyboard velocity",
        PARAM_MC_FILTER_1_KBD_VELOCITY,
        PARAM_CC_FILTER_1_KBD_VELOCITY,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setFilter1KbdVelocity(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.0f%%%s", round(100 * PARAM_SCALE_LINEAR_CENTER_ZERO[value]), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),
    Param(
        PARAM_ID_FILTER_1_ENV_2,
        PARAM_GROUP_NAME_FILTER_MOD,
        "Envelope 2",
        PARAM_MC_FILTER_1_ENV_2,
        PARAM_CC_FILTER_1_ENV_2,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setFilter1Env2(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.0f%%%s", round(100 * PARAM_SCALE_LINEAR_CENTER_ZERO[value]), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),
    Param(
        PARAM_ID_FILTER_1_LFO,
        PARAM_GROUP_NAME_FILTER_MOD,
        "LFO",
        PARAM_MC_FILTER_1_LFO,
        PARAM_CC_FILTER_1_LFO,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setFilter1Lfo(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),
    Param(
        PARAM_ID_FILTER_MODE,
        PARAM_GROUP_NAME_FILTER,
        "Mode",
        PARAM_MC_FILTER_MODE,
        PARAM_NI_FILTER_MODE,
        PARAM_ND_FILTER_MODE,
        0,
        6,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setFilterMode(value); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%s", FILTER_MODE_LABELS[value].c_str()); }),

    // lfo
    Param(
        PARAM_ID_LFO_FREQ,
        PARAM_GROUP_NAME_LFO,
        "Frequency",
        PARAM_MC_LFO_FREQ,
        PARAM_CC_LFO_FREQ,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setLfoFreq(PARAM_SCALE_LFO_FREQ[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.3fhz", PARAM_SCALE_LFO_FREQ[value]); }),
    Param(
        PARAM_ID_LFO_SHAPE,
        PARAM_GROUP_NAME_LFO,
        "Shape",
        PARAM_MC_LFO_SHAPE,
        PARAM_CC_LFO_SHAPE,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setLfoShape(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%%s", round(100.0f * (PARAM_SCALE_LINEAR_CENTER_ZERO[value])), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),
    Param(
        PARAM_ID_LFO_WAVEFORM,
        PARAM_GROUP_NAME_LFO,
        "Waveform",
        PARAM_MC_LFO_WAVEFORM,
        PARAM_NI_LFO_WAVEFORM,
        PARAM_ND_LFO_WAVEFORM,
        4,
        (uint8_t)SYNTH_WAVEFORMS.size() - 1,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setLfoWaveform(value); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return SynthVoice::getSynthWaveformByValue(value).name; }),
    Param(
        PARAM_ID_LFO_ATTACK,
        PARAM_GROUP_NAME_LFO_MOD,
        "Attack",
        PARAM_MC_LFO_ATTACK,
        PARAM_CC_LFO_ATTACK,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnvLfoAttack(PARAM_SCALE_ENV_TIME[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.1fms", PARAM_SCALE_ENV_TIME[value]); }),

    // osc 1/fm
    Param(
        PARAM_ID_OSC_VOLUME_MIX,
        PARAM_GROUP_NAME_MISC,
        "Osc. volume mix",
        PARAM_MC_OSC_VOLUME_MIX,
        PARAM_CC_OSC_VOLUME_MIX,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOscVolumeMix(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("1: %.0f%% 2: %.0f%%", round(100 - 100 * PARAM_SCALE_LINEAR[value]), round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_OSC_1_WAVEFORM,
        PARAM_GROUP_NAME_OSC_1,
        "Waveform",
        PARAM_MC_OSC_1_WAVEFORM,
        PARAM_NI_OSC_1_WAVEFORM,
        PARAM_ND_OSC_1_WAVEFORM,
        0,
        (uint8_t)SYNTH_WAVEFORMS.size() - 1,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1SynthWaveform(value); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return SynthVoice::getSynthWaveformByValue(value).name; }),
    Param(
        PARAM_ID_OSC_FM_WAVEFORM,
        PARAM_GROUP_NAME_OSC_FM,
        "Waveform",
        PARAM_MC_OSC_FM_WAVEFORM,
        PARAM_NI_OSC_FM_WAVEFORM,
        PARAM_ND_OSC_FM_WAVEFORM,
        3,
        (uint8_t)SYNTH_WAVEFORMS.size() - 1,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOscFmSynthWaveform(value); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return SynthVoice::getSynthWaveformByValue(value).name; }),

    Param(
        PARAM_ID_OSC_1_WAVEFOLD,
        PARAM_GROUP_NAME_OSC_1,
        "Wavefold",
        PARAM_MC_OSC_1_WAVEFOLD,
        PARAM_CC_OSC_1_WAVEFOLD,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1WaveFold(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_OSC_1_SHAPE,
        PARAM_GROUP_NAME_OSC_1,
        "Shape",
        PARAM_MC_OSC_1_SHAPE,
        PARAM_CC_OSC_1_SHAPE,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1Shape(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.0f%%%s", round(100 * PARAM_SCALE_LINEAR_CENTER_ZERO[value]), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),

    Param(
        PARAM_ID_OSC_FM_OCTAVE,
        PARAM_GROUP_NAME_OSC_FM,
        "Octave",
        PARAM_MC_OSC_FM_OCTAVE,
        PARAM_NI_OSC_FM_OCTAVE,
        PARAM_ND_OSC_FM_OCTAVE,
        4,
        8,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOscFmOctave((int8_t)map(value, 0, 8, -4, +4)); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+d octaves", map(value, 0, 8, -4, +4)); }),

    Param(
        PARAM_ID_OSC_1_TRANSPOSE,
        PARAM_GROUP_NAME_OSC_1,
        "Transpose",
        PARAM_MC_OSC_1_TRANSPOSE,
        PARAM_NI_OSC_1_TRANSPOSE,
        PARAM_ND_OSC_1_TRANSPOSE,
        12,
        24,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1Transpose((int8_t)map(value, 0, 24, -12, +12)); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+d semitones", map(value, 0, 24, -12, +12)); }),
    Param(
        PARAM_ID_OSC_FM_TRANSPOSE,
        PARAM_GROUP_NAME_OSC_FM,
        "Transpose",
        PARAM_MC_OSC_FM_TRANSPOSE,
        PARAM_NI_OSC_FM_TRANSPOSE,
        PARAM_ND_OSC_FM_TRANSPOSE,
        12,
        24,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOscFmTranspose((int8_t)map(value, 0, 24, -12, +12)); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+d semitones", map(value, 0, 24, -12, +12)); }),

    Param(
        PARAM_ID_OSC_1_DETUNE,
        PARAM_GROUP_NAME_OSC_1,
        "Detune",
        PARAM_MC_OSC_1_DETUNE,
        PARAM_CC_OSC_1_DETUNE,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1Detune(50.0f * PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.0f cents%s", round(50.0f * PARAM_SCALE_LINEAR_CENTER_ZERO[value]), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),

    // osc 1/fm mod
    Param(
        PARAM_ID_OSC_1_MOD_FREQ_ENV_2,
        PARAM_GROUP_NAME_OSC_1_MOD,
        "Frequency env. 2",
        PARAM_MC_OSC_1_MOD_FREQ_ENV_2,
        PARAM_CC_OSC_1_MOD_FREQ_ENV_2,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1ModFreqEnv2(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.0f%%%s", round(100 * PARAM_SCALE_LINEAR_CENTER_ZERO[value]), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),

    Param(
        PARAM_ID_OSC_1_MOD_FREQ_LFO,
        PARAM_GROUP_NAME_OSC_1_MOD,
        "Frequency LFO",
        PARAM_MC_OSC_1_MOD_FREQ_LFO,
        PARAM_CC_OSC_1_MOD_FREQ_LFO,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1ModFreqLfo(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_OSC_1_MOD_SHAPE_ENV_2,
        PARAM_GROUP_NAME_OSC_1_MOD,
        "Shape env. 2",
        PARAM_MC_OSC_1_MOD_SHAPE_ENV_2,
        PARAM_CC_OSC_1_MOD_SHAPE_ENV_2,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1ModShapeEnv2(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.0f%%%s", round(100 * PARAM_SCALE_LINEAR_CENTER_ZERO[value]), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),

    Param(
        PARAM_ID_OSC_1_MOD_SHAPE_LFO,
        PARAM_GROUP_NAME_OSC_1_MOD,
        "Shape LFO",
        PARAM_MC_OSC_1_MOD_SHAPE_LFO,
        PARAM_CC_OSC_1_MOD_SHAPE_LFO,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1ModShapeLfo(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_OSC_1_MOD_WAVEFOLD_ENV_2,
        PARAM_GROUP_NAME_OSC_1_MOD,
        "Wavefold env. 2",
        PARAM_MC_OSC_1_MOD_WAVEFOLD_ENV_2,
        PARAM_CC_OSC_1_MOD_WAVEFOLD_ENV_2,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1ModWaveFoldEnv2(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.0f%%%s", round(100 * PARAM_SCALE_LINEAR_CENTER_ZERO[value]), zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),

    Param(
        PARAM_ID_OSC_1_UNISON_DETUNE,
        PARAM_GROUP_NAME_OSC_1,
        "Unison detune",
        PARAM_MC_OSC_1_UNISON_DETUNE,
        PARAM_CC_OSC_1_UNISON_DETUNE,
        51,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1UnisonDetune(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_OSC_1_UNISON_MIX,
        PARAM_GROUP_NAME_OSC_1,
        "Unison mix",
        PARAM_MC_OSC_1_UNISON_MIX,
        PARAM_CC_OSC_1_UNISON_MIX,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOsc1UnisonMix(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_OSC_FM_MOD_PHASE_MOD_ENV_2,
        PARAM_GROUP_NAME_OSC_FM_MOD,
        "Phase env. 2",
        PARAM_MC_OSC_FM_MOD_PHASE_MOD_ENV_2,
        PARAM_CC_OSC_FM_MOD_PHASE_MOD_ENV_2,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOscFmModPhaseEnv2(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_OSC_FM_PHASE_MOD,
        PARAM_GROUP_NAME_OSC_FM,
        "Phase modulation",
        PARAM_MC_OSC_FM_PHASE_MOD,
        PARAM_CC_OSC_FM_PHASE_MOD,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setOscFmPhaseMod(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_FILTER_2_FREQ_OFFSET,
        PARAM_GROUP_NAME_FILTER,
        "Filter 2 freq. offset",
        PARAM_MC_FILTER_2_FREQ_OFFSET,
        PARAM_CC_FILTER_2_FREQ_OFFSET,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setFilter2FrequencyOffset(PARAM_SCALE_LINEAR_CENTER_ZERO[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%+.1f semitones%s", 48.0f * PARAM_SCALE_LINEAR_CENTER_ZERO[value], zeroSuffix(PARAM_SCALE_LINEAR_CENTER_ZERO[value]).c_str()); }),

    // waveshape
    Param(
        PARAM_ID_WAVESHAPE_LEVEL,
        PARAM_GROUP_NAME_MISC,
        "Waveshape level",
        PARAM_MC_WAVESHAPE_LEVEL,
        PARAM_CC_WAVESHAPE_LEVEL,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setWaveshapeLevel(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_PITCH_CHANGE_RANGE,
        PARAM_GROUP_NAME_MISC,
        "Pitch change range",
        PARAM_MC_PITCH_CHANGE_RANGE_LEVEL,
        PARAM_NI_PITCH_CHANGE_RANGE_LEVEL,
        PARAM_ND_PITCH_CHANGE_RANGE_LEVEL,
        2,
        12,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setPitchChangeRange(value); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%d semitones", value); }),

    Param(
        PARAM_ID_AMP_MOD_LFO,
        PARAM_GROUP_NAME_AMP_MOD,
        "Volume LFO",
        PARAM_MC_AMP_MOD_LFO,
        PARAM_CC_AMP_MOD_LFO,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setAmpModLfo(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_AMP_KBD_VELOCITY,
        PARAM_MI_AMP_KBD_VELOCITY,
        PARAM_GROUP_NAME_AMP_MOD,
        "Keyboard velocity",
        PARAM_MC_AMP_KBD_VELOCITY,
        64,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setAmpKbdVelocity(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_ENSEMBLE_MIX,
        PARAM_GROUP_NAME_MISC,
        "Ensemble mix",
        PARAM_MC_ENSEMBLE_MIX,
        PARAM_CC_ENSEMBLE_MIX,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnsembleMix(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

    Param(
        PARAM_ID_ENSEMBLE_LFO_RATE,
        PARAM_GROUP_NAME_MISC,
        "Ensemble LFO rate",
        PARAM_MC_ENSEMBLE_LFO_RATE,
        PARAM_CC_ENSEMBLE_LFO_RATE,
        63,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnsembleLfoRate(PARAM_SCALE_LFO_FREQ[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.3fhz", PARAM_SCALE_LFO_FREQ[value]); }),

    Param(
        PARAM_ID_MOD_WHL_ENV_REVERSE,
        PARAM_MI_MOD_WHL_ENV_REVERSE,
        PARAM_GROUP_NAME_MOD_WHL,
        "ENV reverse",
        PARAM_MC_MOD_WHL_ENV_REVERSE,
        0,
        127,
        []([[maybe_unused]] const Param *param, Synth &synth, const uint8_t value)
        { synth.setEnvReverse(PARAM_SCALE_LINEAR[value]); },
        []([[maybe_unused]] const Param *param, const uint8_t value)
        { return formatString("%.0f%%", round(100 * PARAM_SCALE_LINEAR[value])); }),

};

#endif