#ifndef ConstantValues_h
#define ConstantValues_h

#include <stdint.h>
#include <array>
#include <map>
#include <string>

// this file contains various constants used throughout the code


// labels to describe the filter modes
const std::array<const std::string, 7> FILTER_MODE_LABELS{{"1:LPF12 & 2:LPF12", "1:LPF12 & 2:HPF12", "1:HPF12 & 2:LPF12", "1:HPF12 & 2:HPF12", "1:LPF12", "1:HPF12", "Bypass"}};


// MIDImix, using the default layout
// dial control changes
PROGMEM static const uint8_t MIDIMIX_CH_1_DAIL_1_CC{16};
PROGMEM static const uint8_t MIDIMIX_CH_2_DAIL_1_CC{20};
PROGMEM static const uint8_t MIDIMIX_CH_3_DAIL_1_CC{24};
PROGMEM static const uint8_t MIDIMIX_CH_4_DAIL_1_CC{28};
PROGMEM static const uint8_t MIDIMIX_CH_5_DAIL_1_CC{46};
PROGMEM static const uint8_t MIDIMIX_CH_6_DAIL_1_CC{50};
PROGMEM static const uint8_t MIDIMIX_CH_7_DAIL_1_CC{54};
PROGMEM static const uint8_t MIDIMIX_CH_8_DAIL_1_CC{58};

PROGMEM static const uint8_t MIDIMIX_CH_1_DAIL_2_CC{17};
PROGMEM static const uint8_t MIDIMIX_CH_2_DAIL_2_CC{21};
PROGMEM static const uint8_t MIDIMIX_CH_3_DAIL_2_CC{25};
PROGMEM static const uint8_t MIDIMIX_CH_4_DAIL_2_CC{29};
PROGMEM static const uint8_t MIDIMIX_CH_5_DAIL_2_CC{47};
PROGMEM static const uint8_t MIDIMIX_CH_6_DAIL_2_CC{51};
PROGMEM static const uint8_t MIDIMIX_CH_7_DAIL_2_CC{55};
PROGMEM static const uint8_t MIDIMIX_CH_8_DAIL_2_CC{59};

PROGMEM static const uint8_t MIDIMIX_CH_1_DAIL_3_CC{18};
PROGMEM static const uint8_t MIDIMIX_CH_2_DAIL_3_CC{22};
PROGMEM static const uint8_t MIDIMIX_CH_3_DAIL_3_CC{26};
PROGMEM static const uint8_t MIDIMIX_CH_4_DAIL_3_CC{30};
PROGMEM static const uint8_t MIDIMIX_CH_5_DAIL_3_CC{48};
PROGMEM static const uint8_t MIDIMIX_CH_6_DAIL_3_CC{52};
PROGMEM static const uint8_t MIDIMIX_CH_7_DAIL_3_CC{56};
PROGMEM static const uint8_t MIDIMIX_CH_8_DAIL_3_CC{60};

// mute button notes
PROGMEM static const uint8_t MIDIMIX_CH_1_MUTE_NT{1};
PROGMEM static const uint8_t MIDIMIX_CH_2_MUTE_NT{4};
PROGMEM static const uint8_t MIDIMIX_CH_3_MUTE_NT{7};
PROGMEM static const uint8_t MIDIMIX_CH_4_MUTE_NT{10};
PROGMEM static const uint8_t MIDIMIX_CH_5_MUTE_NT{13};
PROGMEM static const uint8_t MIDIMIX_CH_6_MUTE_NT{16};
PROGMEM static const uint8_t MIDIMIX_CH_7_MUTE_NT{19};
PROGMEM static const uint8_t MIDIMIX_CH_8_MUTE_NT{22};

// solo button notes
PROGMEM static const uint8_t MIDIMIX_CH_1_SOLO_NT{2};
PROGMEM static const uint8_t MIDIMIX_CH_2_SOLO_NT{5};
PROGMEM static const uint8_t MIDIMIX_CH_3_SOLO_NT{8};
PROGMEM static const uint8_t MIDIMIX_CH_4_SOLO_NT{11};
PROGMEM static const uint8_t MIDIMIX_CH_5_SOLO_NT{14};
PROGMEM static const uint8_t MIDIMIX_CH_6_SOLO_NT{17};
PROGMEM static const uint8_t MIDIMIX_CH_7_SOLO_NT{20};
PROGMEM static const uint8_t MIDIMIX_CH_8_SOLO_NT{23};

// rec/arm button notes
PROGMEM static const uint8_t MIDIMIX_CH_1_REC_ARM_NT{3};
PROGMEM static const uint8_t MIDIMIX_CH_2_REC_ARM_NT{6};
PROGMEM static const uint8_t MIDIMIX_CH_3_REC_ARM_NT{9};
PROGMEM static const uint8_t MIDIMIX_CH_4_REC_ARM_NT{12};
PROGMEM static const uint8_t MIDIMIX_CH_5_REC_ARM_NT{15};
PROGMEM static const uint8_t MIDIMIX_CH_6_REC_ARM_NT{18};
PROGMEM static const uint8_t MIDIMIX_CH_7_REC_ARM_NT{21};
PROGMEM static const uint8_t MIDIMIX_CH_8_REC_ARM_NT{24};

// slider control changes
PROGMEM static const uint8_t MIDIMIX_CH_1_SLIDER_CC{19};
PROGMEM static const uint8_t MIDIMIX_CH_2_SLIDER_CC{23};
PROGMEM static const uint8_t MIDIMIX_CH_3_SLIDER_CC{27};
PROGMEM static const uint8_t MIDIMIX_CH_4_SLIDER_CC{31};
PROGMEM static const uint8_t MIDIMIX_CH_5_SLIDER_CC{49};
PROGMEM static const uint8_t MIDIMIX_CH_6_SLIDER_CC{53};
PROGMEM static const uint8_t MIDIMIX_CH_7_SLIDER_CC{57};
PROGMEM static const uint8_t MIDIMIX_CH_8_SLIDER_CC{61};

// action button notes
PROGMEM static const uint8_t MIDIMIX_BANK_LEFT_NT{25};
PROGMEM static const uint8_t MIDIMIX_BANK_RIGHT_NT{26};
PROGMEM static const uint8_t MIDIMIX_SOLO_NT{27};

// master slider control change
PROGMEM static const uint8_t MIDIMIX_MASTER_SLIDER_CC{62};


// 4 byte signature used for patch files
const char FILE_SIGNATURE[]{"TMP0"};
const uint8_t FILE_SIGNATURE_SIZE{4};

// generic transition speed for some of the controls
const float TRANSITION_SPEED_MS{2.0f};


// mappings to describe the functions of the MIDImix buttons

// action buttons notes
const uint8_t CONTROL_NT_LOAD{MIDIMIX_BANK_LEFT_NT};
const uint8_t CONTROL_NT_SAVE{MIDIMIX_BANK_RIGHT_NT};
const uint8_t CONTROL_NT_MENU{MIDIMIX_SOLO_NT};

// increment / decrement buttons notes
const uint8_t CONTROL_NI_VALUE_1{MIDIMIX_CH_1_MUTE_NT};
const uint8_t CONTROL_ND_VALUE_1{MIDIMIX_CH_1_REC_ARM_NT};
const uint8_t CONTROL_NI_VALUE_2{MIDIMIX_CH_2_MUTE_NT};
const uint8_t CONTROL_ND_VALUE_2{MIDIMIX_CH_2_REC_ARM_NT};
const uint8_t CONTROL_NI_VALUE_3{MIDIMIX_CH_3_MUTE_NT};
const uint8_t CONTROL_ND_VALUE_3{MIDIMIX_CH_3_REC_ARM_NT};
const uint8_t CONTROL_NI_VALUE_4{MIDIMIX_CH_4_MUTE_NT};
const uint8_t CONTROL_ND_VALUE_4{MIDIMIX_CH_4_REC_ARM_NT};
const uint8_t CONTROL_NI_VALUE_5{MIDIMIX_CH_5_MUTE_NT};
const uint8_t CONTROL_ND_VALUE_5{MIDIMIX_CH_5_REC_ARM_NT};
const uint8_t CONTROL_NI_VALUE_6{MIDIMIX_CH_6_MUTE_NT};
const uint8_t CONTROL_ND_VALUE_6{MIDIMIX_CH_6_REC_ARM_NT};
const uint8_t CONTROL_NI_VALUE_7{MIDIMIX_CH_7_MUTE_NT};
const uint8_t CONTROL_ND_VALUE_7{MIDIMIX_CH_7_REC_ARM_NT};
const uint8_t CONTROL_NI_VALUE_8{MIDIMIX_CH_8_MUTE_NT};
const uint8_t CONTROL_ND_VALUE_8{MIDIMIX_CH_8_REC_ARM_NT};

// increment button note to value map
const std::map<uint8_t, uint8_t> CONTROL_NI_VALUE_MAP{
    {CONTROL_NI_VALUE_1, 1},
    {CONTROL_NI_VALUE_2, 2},
    {CONTROL_NI_VALUE_3, 3},
    {CONTROL_NI_VALUE_4, 4},
    {CONTROL_NI_VALUE_5, 5},
    {CONTROL_NI_VALUE_6, 6},
    {CONTROL_NI_VALUE_7, 7},
    {CONTROL_NI_VALUE_8, 8}
};

// decrement button note to value map
const std::map<uint8_t, uint8_t> CONTROL_ND_VALUE_MAP{
    {CONTROL_ND_VALUE_1, 1},
    {CONTROL_ND_VALUE_2, 2},
    {CONTROL_ND_VALUE_3, 3},
    {CONTROL_ND_VALUE_4, 4},
    {CONTROL_ND_VALUE_5, 5},
    {CONTROL_ND_VALUE_6, 6},
    {CONTROL_ND_VALUE_7, 7},
    {CONTROL_ND_VALUE_8, 8}
};

// increment value to button note map
const std::map<uint8_t, uint8_t> CONTROL_VALUE_NI_MAP{
    {1, CONTROL_NI_VALUE_1},
    {2, CONTROL_NI_VALUE_2},
    {3, CONTROL_NI_VALUE_3},
    {4, CONTROL_NI_VALUE_4},
    {5, CONTROL_NI_VALUE_5},
    {6, CONTROL_NI_VALUE_6},
    {7, CONTROL_NI_VALUE_7},
    {8, CONTROL_NI_VALUE_8}
};

// decrement value to button note map
const std::map<uint8_t, uint8_t> CONTROL_VALUE_ND_MAP{
    {1, CONTROL_ND_VALUE_1},
    {2, CONTROL_ND_VALUE_2},
    {3, CONTROL_ND_VALUE_3},
    {4, CONTROL_ND_VALUE_4},
    {5, CONTROL_ND_VALUE_5},
    {6, CONTROL_ND_VALUE_6},
    {7, CONTROL_ND_VALUE_7},
    {8, CONTROL_ND_VALUE_8}
};


// param group names
const std::string PARAM_GROUP_NAME_ENV_1{"Envelope 1"};
const std::string PARAM_GROUP_NAME_ENV_2{"Envelope 2"};
const std::string PARAM_GROUP_NAME_FILTER{"Filters"};
const std::string PARAM_GROUP_NAME_FILTER_MOD{"Filter modulation"};
const std::string PARAM_GROUP_NAME_LFO{"LFO"};
const std::string PARAM_GROUP_NAME_LFO_MOD{"LFO modulation"};
const std::string PARAM_GROUP_NAME_OSC_1{"Oscillator 1"};
const std::string PARAM_GROUP_NAME_OSC_1_MOD{"Osc. 1 modulation"};
const std::string PARAM_GROUP_NAME_OSC_FM{"Oscillator FM"};
const std::string PARAM_GROUP_NAME_OSC_FM_MOD{"Osc. FM modulation"};
const std::string PARAM_GROUP_NAME_AMP_MOD{"Amplifier modulation"};
const std::string PARAM_GROUP_NAME_MISC{"Miscellaneous"};
const std::string PARAM_GROUP_NAME_MOD_WHL{"Modulation wheel"};


// constant for params
// PARAM_ID_* contains the ID of the parameter, also used in the stored patches
// PARAM_CC_* contains the control change sent out by the MIDImix
// PARAM_NI_* contains the note increment sent out by the MIDImix
// PARAM_ND_* contains the note decrement sent out by the MIDImix
// PARAM_MC_* contains the control change used when communicating with external MIDI (DAW)


// envelope 1
const uint16_t PARAM_ID_ENV_1_ATTACK{0};
const uint16_t PARAM_ID_ENV_1_DECAY{1};
const uint16_t PARAM_ID_ENV_1_SUSTAIN{2};
const uint16_t PARAM_ID_ENV_1_RELEASE{3};

const uint8_t PARAM_CC_ENV_1_ATTACK{MIDIMIX_CH_1_SLIDER_CC};
const uint8_t PARAM_CC_ENV_1_DECAY{MIDIMIX_CH_2_SLIDER_CC};
const uint8_t PARAM_CC_ENV_1_SUSTAIN{MIDIMIX_CH_3_SLIDER_CC};
const uint8_t PARAM_CC_ENV_1_RELEASE{MIDIMIX_CH_4_SLIDER_CC};

const uint8_t PARAM_MC_ENV_1_ATTACK{73};
const uint8_t PARAM_MC_ENV_1_DECAY{75};
const uint8_t PARAM_MC_ENV_1_SUSTAIN{79};
const uint8_t PARAM_MC_ENV_1_RELEASE{72};

// envelope 2
const uint16_t PARAM_ID_ENV_2_ATTACK{100};
const uint16_t PARAM_ID_ENV_2_DECAY{101};
const uint16_t PARAM_ID_ENV_2_SUSTAIN{102};
const uint16_t PARAM_ID_ENV_2_RELEASE{103};

const uint8_t PARAM_CC_ENV_2_ATTACK{MIDIMIX_CH_5_SLIDER_CC};
const uint8_t PARAM_CC_ENV_2_DECAY{MIDIMIX_CH_6_SLIDER_CC};
const uint8_t PARAM_CC_ENV_2_SUSTAIN{MIDIMIX_CH_7_SLIDER_CC};
const uint8_t PARAM_CC_ENV_2_RELEASE{MIDIMIX_CH_8_SLIDER_CC};

const uint8_t PARAM_MC_ENV_2_ATTACK{16};
const uint8_t PARAM_MC_ENV_2_DECAY{17};
const uint8_t PARAM_MC_ENV_2_SUSTAIN{18};
const uint8_t PARAM_MC_ENV_2_RELEASE{19};

// filter
const uint16_t PARAM_ID_FILTER_1_FREQ{200};
const uint16_t PARAM_ID_FILTER_1_RES{201};
const uint16_t PARAM_ID_FILTER_1_KBD_TRACK{202};
const uint16_t PARAM_ID_FILTER_1_KBD_VELOCITY{203};
const uint16_t PARAM_ID_FILTER_1_ENV_2{205};
const uint16_t PARAM_ID_FILTER_1_LFO{206};
const uint16_t PARAM_ID_FILTER_MODE{207};

const uint8_t PARAM_CC_FILTER_1_FREQ{MIDIMIX_MASTER_SLIDER_CC};
const uint8_t PARAM_CC_FILTER_1_RES{MIDIMIX_CH_8_DAIL_3_CC};
const uint8_t PARAM_MI_FILTER_1_KBD_TRACK{1};
const uint8_t PARAM_CC_FILTER_1_KBD_VELOCITY{MIDIMIX_CH_8_DAIL_1_CC};
const uint8_t PARAM_CC_FILTER_1_ENV_2{MIDIMIX_CH_6_DAIL_1_CC};
const uint8_t PARAM_CC_FILTER_1_LFO{MIDIMIX_CH_7_DAIL_1_CC};
const uint8_t PARAM_NI_FILTER_MODE{MIDIMIX_CH_4_MUTE_NT};
const uint8_t PARAM_ND_FILTER_MODE{MIDIMIX_CH_4_REC_ARM_NT};

const uint8_t PARAM_MC_FILTER_1_FREQ{74};
const uint8_t PARAM_MC_FILTER_1_RES{71};
const uint8_t PARAM_MC_FILTER_1_KBD_TRACK{20};
const uint8_t PARAM_MC_FILTER_1_KBD_VELOCITY{21};
const uint8_t PARAM_MC_FILTER_1_ENV_2{22};
const uint8_t PARAM_MC_FILTER_1_LFO{23};
const uint8_t PARAM_MC_FILTER_MODE{24};

// lfo
const uint16_t PARAM_ID_LFO_FREQ{300};
const uint16_t PARAM_ID_LFO_SHAPE{301};
const uint16_t PARAM_ID_LFO_WAVEFORM{302};
const uint16_t PARAM_ID_LFO_ATTACK{303};

const uint8_t PARAM_CC_LFO_FREQ{MIDIMIX_CH_5_DAIL_1_CC};
const uint8_t PARAM_CC_LFO_SHAPE{MIDIMIX_CH_5_DAIL_2_CC};
const uint8_t PARAM_NI_LFO_WAVEFORM{MIDIMIX_CH_5_MUTE_NT};
const uint8_t PARAM_ND_LFO_WAVEFORM{MIDIMIX_CH_5_REC_ARM_NT};
const uint8_t PARAM_CC_LFO_ATTACK{MIDIMIX_CH_5_DAIL_3_CC};

const uint8_t PARAM_MC_LFO_FREQ{76};
const uint8_t PARAM_MC_LFO_SHAPE{25};
const uint8_t PARAM_MC_LFO_WAVEFORM{26};
const uint8_t PARAM_MC_LFO_ATTACK{78};

// osc1
const uint16_t PARAM_ID_OSC_1_WAVEFORM{501};
const uint16_t PARAM_ID_OSC_1_WAVEFOLD{502};
const uint16_t PARAM_ID_OSC_1_SHAPE{503};
const uint16_t PARAM_ID_OSC_1_TRANSPOSE{505};
const uint16_t PARAM_ID_OSC_1_DETUNE{506};

const uint8_t PARAM_NI_OSC_1_WAVEFORM{MIDIMIX_CH_1_MUTE_NT};
const uint8_t PARAM_ND_OSC_1_WAVEFORM{MIDIMIX_CH_1_REC_ARM_NT};
const uint8_t PARAM_CC_OSC_1_WAVEFOLD{MIDIMIX_CH_2_DAIL_3_CC};
const uint8_t PARAM_CC_OSC_1_SHAPE{MIDIMIX_CH_2_DAIL_2_CC};
const uint8_t PARAM_NI_OSC_1_TRANSPOSE{MIDIMIX_CH_2_MUTE_NT};
const uint8_t PARAM_ND_OSC_1_TRANSPOSE{MIDIMIX_CH_2_REC_ARM_NT};
const uint8_t PARAM_CC_OSC_1_DETUNE{MIDIMIX_CH_2_DAIL_1_CC};

const uint8_t PARAM_MC_OSC_1_WAVEFORM{27};
const uint8_t PARAM_MC_OSC_1_WAVEFOLD{28};
const uint8_t PARAM_MC_OSC_1_SHAPE{29};
const uint8_t PARAM_MC_OSC_1_TRANSPOSE{30};
const uint8_t PARAM_MC_OSC_1_DETUNE{31};

// osc1 mod
const uint16_t PARAM_ID_OSC_1_MOD_FREQ_ENV_2{601};
const uint16_t PARAM_ID_OSC_1_MOD_FREQ_LFO{602};
const uint16_t PARAM_ID_OSC_1_MOD_SHAPE_ENV_2{604};
const uint16_t PARAM_ID_OSC_1_MOD_SHAPE_LFO{605};
const uint16_t PARAM_ID_OSC_1_MOD_WAVEFOLD_ENV_2{607};
const uint16_t PARAM_ID_OSC_1_UNISON_DETUNE{609};
const uint16_t PARAM_ID_OSC_1_UNISON_MIX{610};

const uint8_t PARAM_CC_OSC_1_MOD_FREQ_ENV_2{MIDIMIX_CH_3_DAIL_1_CC};
const uint8_t PARAM_CC_OSC_1_MOD_FREQ_LFO{MIDIMIX_CH_4_DAIL_1_CC};
const uint8_t PARAM_CC_OSC_1_MOD_SHAPE_ENV_2{MIDIMIX_CH_3_DAIL_2_CC};
const uint8_t PARAM_CC_OSC_1_MOD_SHAPE_LFO{MIDIMIX_CH_4_DAIL_2_CC};
const uint8_t PARAM_CC_OSC_1_MOD_WAVEFOLD_ENV_2{255};
const uint8_t PARAM_CC_OSC_1_UNISON_DETUNE{MIDIMIX_CH_1_DAIL_2_CC};
const uint8_t PARAM_CC_OSC_1_UNISON_MIX{MIDIMIX_CH_1_DAIL_3_CC};

const uint8_t PARAM_MC_OSC_1_MOD_FREQ_ENV_2{80};
const uint8_t PARAM_MC_OSC_1_MOD_FREQ_LFO{81};
const uint8_t PARAM_MC_OSC_1_MOD_SHAPE_ENV_2{82};
const uint8_t PARAM_MC_OSC_1_MOD_SHAPE_LFO{83};
const uint8_t PARAM_MC_OSC_1_MOD_WAVEFOLD_ENV_2{85};
const uint8_t PARAM_MC_OSC_1_UNISON_DETUNE{86};
const uint8_t PARAM_MC_OSC_1_UNISON_MIX{87};

// osc fm
const uint16_t PARAM_ID_OSC_FM_WAVEFORM{901};
const uint16_t PARAM_ID_OSC_FM_OCTAVE{904};
const uint16_t PARAM_ID_OSC_FM_TRANSPOSE{905};

const uint8_t PARAM_NI_OSC_FM_WAVEFORM{MIDIMIX_CH_6_MUTE_NT};
const uint8_t PARAM_ND_OSC_FM_WAVEFORM{MIDIMIX_CH_6_REC_ARM_NT};
const uint8_t PARAM_NI_OSC_FM_OCTAVE{MIDIMIX_CH_7_MUTE_NT};
const uint8_t PARAM_ND_OSC_FM_OCTAVE{MIDIMIX_CH_7_REC_ARM_NT};
const uint8_t PARAM_NI_OSC_FM_TRANSPOSE{MIDIMIX_CH_8_MUTE_NT};
const uint8_t PARAM_ND_OSC_FM_TRANSPOSE{MIDIMIX_CH_8_REC_ARM_NT};

const uint8_t PARAM_MC_OSC_FM_WAVEFORM{88};
const uint8_t PARAM_MC_OSC_FM_OCTAVE{89};
const uint8_t PARAM_MC_OSC_FM_TRANSPOSE{90};

// osc fm mod
const uint16_t PARAM_ID_OSC_FM_MOD_PHASE_MOD_ENV_2{1011};
const uint16_t PARAM_ID_OSC_FM_PHASE_MOD{1013};

const uint8_t PARAM_CC_OSC_FM_MOD_PHASE_MOD_ENV_2{MIDIMIX_CH_6_DAIL_3_CC};
const uint8_t PARAM_CC_OSC_FM_PHASE_MOD{MIDIMIX_CH_6_DAIL_2_CC};

const uint8_t PARAM_MC_OSC_FM_MOD_PHASE_MOD_ENV_2{102};
const uint8_t PARAM_MC_OSC_FM_PHASE_MOD{103};

// filter2
const uint16_t PARAM_ID_FILTER_2_FREQ_OFFSET{1200};

const uint8_t PARAM_CC_FILTER_2_FREQ_OFFSET{MIDIMIX_CH_8_DAIL_2_CC};

const uint8_t PARAM_MC_FILTER_2_FREQ_OFFSET{81};

// misc
const uint16_t PARAM_ID_WAVESHAPE_LEVEL{1300};
const uint16_t PARAM_ID_PITCH_CHANGE_RANGE{1301};
const uint16_t PARAM_ID_OSC_VOLUME_MIX{1302};
const uint16_t PARAM_ID_ENSEMBLE_MIX{1303};
const uint16_t PARAM_ID_ENSEMBLE_LFO_RATE{1304};

const uint8_t PARAM_CC_WAVESHAPE_LEVEL{MIDIMIX_CH_3_DAIL_3_CC};
const uint8_t PARAM_NI_PITCH_CHANGE_RANGE_LEVEL{MIDIMIX_CH_3_MUTE_NT};
const uint8_t PARAM_ND_PITCH_CHANGE_RANGE_LEVEL{MIDIMIX_CH_3_REC_ARM_NT};
const uint8_t PARAM_CC_OSC_VOLUME_MIX{MIDIMIX_CH_1_DAIL_1_CC};
const uint8_t PARAM_CC_ENSEMBLE_MIX{MIDIMIX_CH_7_DAIL_3_CC};
const uint8_t PARAM_CC_ENSEMBLE_LFO_RATE{MIDIMIX_CH_7_DAIL_2_CC};

const uint8_t PARAM_MC_WAVESHAPE_LEVEL{104};
const uint8_t PARAM_MC_PITCH_CHANGE_RANGE_LEVEL{105};
const uint8_t PARAM_MC_OSC_VOLUME_MIX{106};
const uint8_t PARAM_MC_ENSEMBLE_MIX{93};
const uint8_t PARAM_MC_ENSEMBLE_LFO_RATE{94};

// amp
const uint16_t PARAM_ID_AMP_MOD_LFO{1400};
const uint16_t PARAM_ID_AMP_KBD_VELOCITY{1401};

const uint8_t PARAM_CC_AMP_MOD_LFO{MIDIMIX_CH_4_DAIL_3_CC};
const uint8_t PARAM_MI_AMP_KBD_VELOCITY{2};

const uint8_t PARAM_MC_AMP_MOD_LFO{92};
const uint8_t PARAM_MC_AMP_KBD_VELOCITY{95};

// menu
const uint16_t PARAM_ID_MOD_WHL_ENV_REVERSE{1500};

const uint8_t PARAM_MI_MOD_WHL_ENV_REVERSE{0};

const uint8_t PARAM_MC_MOD_WHL_ENV_REVERSE{107};

#endif