#ifndef ConstantSynthWaveforms_h
#define ConstantSynthWaveforms_h

#include <vector>
#include <Audio.h>
#include "SynthWaveform.h"

#include "AKWF_WaveForms/AKWF_aguitar.h"
#include "AKWF_WaveForms/AKWF_altosax.h"
#include "AKWF_WaveForms/AKWF_cello.h"
#include "AKWF_WaveForms/AKWF_clarinett.h"
#include "AKWF_WaveForms/AKWF_clavinet.h"
#include "AKWF_WaveForms/AKWF_dbass.h"
#include "AKWF_WaveForms/AKWF_ebass.h"
#include "AKWF_WaveForms/AKWF_eguitar.h"
#include "AKWF_WaveForms/AKWF_eorgan.h"
#include "AKWF_WaveForms/AKWF_epiano.h"
#include "AKWF_WaveForms/AKWF_flute.h"
#include "AKWF_WaveForms/AKWF_hvoice.h"
#include "AKWF_WaveForms/AKWF_oboe.h"
#include "AKWF_WaveForms/AKWF_piano.h"
#include "AKWF_WaveForms/AKWF_snippet.h"

// waveforms available to the oscillators:
const std::vector<SynthWaveform> SYNTH_WAVEFORMS{
    {"Sawtooth", WAVEFORM_BANDLIMIT_SAWTOOTH, nullptr},
    {"Sawtooth (reverse)", WAVEFORM_BANDLIMIT_SAWTOOTH_REVERSE, nullptr},
    {"Square (w/shape)", WAVEFORM_BANDLIMIT_PULSE, nullptr},
    {"Sine", WAVEFORM_SINE, nullptr},
    {"Triangle (w/shape)", WAVEFORM_TRIANGLE_VARIABLE, nullptr},
    {"Sample & hold noise", WAVEFORM_SAMPLE_HOLD, nullptr},
    {"Wave - Ac. guitar 1", WAVEFORM_ARBITRARY, AKWF_aguitar_0001},
    {"Wave - Ac. guitar 2", WAVEFORM_ARBITRARY, AKWF_aguitar_0002},
    {"Wave - Ac. guitar 3", WAVEFORM_ARBITRARY, AKWF_aguitar_0005},
    {"Wave - Ac. guitar 4", WAVEFORM_ARBITRARY, AKWF_aguitar_0007},
    {"Wave - Ac. guitar 5", WAVEFORM_ARBITRARY, AKWF_aguitar_0009},
    {"Wave - Ac. guitar 6", WAVEFORM_ARBITRARY, AKWF_aguitar_0016},
    {"Wave - Alto sax 1", WAVEFORM_ARBITRARY, AKWF_altosax_0001},
    {"Wave - Alto sax 2", WAVEFORM_ARBITRARY, AKWF_altosax_0007},
    {"Wave - Alto sax 3", WAVEFORM_ARBITRARY, AKWF_altosax_0008},
    {"Wave - Cello 1", WAVEFORM_ARBITRARY, AKWF_cello_0002},
    {"Wave - Cello 2", WAVEFORM_ARBITRARY, AKWF_cello_0003},
    {"Wave - Cello 3", WAVEFORM_ARBITRARY, AKWF_cello_0004},
    {"Wave - Clarinett 1", WAVEFORM_ARBITRARY, AKWF_clarinett_0001},
    {"Wave - Clarinett 2", WAVEFORM_ARBITRARY, AKWF_clarinett_0002},
    {"Wave - Clarinett 3", WAVEFORM_ARBITRARY, AKWF_clarinett_0003},
    {"Wave - Clavinet", WAVEFORM_ARBITRARY, AKWF_clavinet_0001},
    {"Wave - Double bass", WAVEFORM_ARBITRARY, AKWF_dbass_0001},
    {"Wave - Elec. bass 1", WAVEFORM_ARBITRARY, AKWF_ebass_0012},
    {"Wave - Elec. bass 2", WAVEFORM_ARBITRARY, AKWF_ebass_0032},
    {"Wave - Elec. bass 3", WAVEFORM_ARBITRARY, AKWF_ebass_0034},
    {"Wave - Elec. organ 1", WAVEFORM_ARBITRARY, AKWF_eorgan_0003},
    {"Wave - Elec. organ 2", WAVEFORM_ARBITRARY, AKWF_eorgan_0020},
    {"Wave - Elec. organ 3", WAVEFORM_ARBITRARY, AKWF_eorgan_0030},
    {"Wave - Elec. organ 4", WAVEFORM_ARBITRARY, AKWF_eorgan_0032},
    {"Wave - Elec. piano 1", WAVEFORM_ARBITRARY, AKWF_epiano_0001},
    {"Wave - Elec. piano 2", WAVEFORM_ARBITRARY, AKWF_epiano_0005},
    {"Wave - Elec. piano 3", WAVEFORM_ARBITRARY, AKWF_epiano_0013},
    {"Wave - Elec. piano 4", WAVEFORM_ARBITRARY, AKWF_epiano_0016},
    {"Wave - Flute 1", WAVEFORM_ARBITRARY, AKWF_flute_0001},
    {"Wave - Human voice 1", WAVEFORM_ARBITRARY, AKWF_hvoice_0009},
    {"Wave - Human voice 2", WAVEFORM_ARBITRARY, AKWF_hvoice_0010},
    {"Wave - Human voice 3", WAVEFORM_ARBITRARY, AKWF_hvoice_0011},
    {"Wave - Human voice 4", WAVEFORM_ARBITRARY, AKWF_hvoice_0012},
    {"Wave - Oboe 1", WAVEFORM_ARBITRARY, AKWF_oboe_0001},
    {"Wave - Oboe 2", WAVEFORM_ARBITRARY, AKWF_oboe_0002},
    {"Wave - Oboe 3", WAVEFORM_ARBITRARY, AKWF_oboe_0003},
    {"Wave - Oboe 4", WAVEFORM_ARBITRARY, AKWF_oboe_0004},
    {"Wave - Oboe 5", WAVEFORM_ARBITRARY, AKWF_oboe_0005},
    {"Wave - Piano 1", WAVEFORM_ARBITRARY, AKWF_piano_0001},
    {"Wave - Piano 2", WAVEFORM_ARBITRARY, AKWF_piano_0002},
    {"Wave - Piano 3", WAVEFORM_ARBITRARY, AKWF_piano_0005},
    {"Wave - Snippet 1", WAVEFORM_ARBITRARY, AKWF_snippet_0001},
    {"Wave - Snippet 2", WAVEFORM_ARBITRARY, AKWF_snippet_0002},
    {"Wave - Snippet 3", WAVEFORM_ARBITRARY, AKWF_snippet_0003},
    {"Wave - Snippet 4", WAVEFORM_ARBITRARY, AKWF_snippet_0004},
    {"Wave - Snippet 5", WAVEFORM_ARBITRARY, AKWF_snippet_0005},
    {"Wave - Snippet 6", WAVEFORM_ARBITRARY, AKWF_snippet_0006},
    {"Wave - Snippet 7", WAVEFORM_ARBITRARY, AKWF_snippet_0007},
    {"Wave - Snippet 8", WAVEFORM_ARBITRARY, AKWF_snippet_0008},
    {"Wave - Snippet 9", WAVEFORM_ARBITRARY, AKWF_snippet_0009},
    {"Wave - Snippet 10", WAVEFORM_ARBITRARY, AKWF_snippet_0010},
    {"Wave - Snippet 11", WAVEFORM_ARBITRARY, AKWF_snippet_0011},
    {"Wave - Snippet 12", WAVEFORM_ARBITRARY, AKWF_snippet_0012},
    {"Wave - Snippet 13", WAVEFORM_ARBITRARY, AKWF_snippet_0013},
    {"Wave - Snippet 14", WAVEFORM_ARBITRARY, AKWF_snippet_0014},
    {"Wave - Snippet 15", WAVEFORM_ARBITRARY, AKWF_snippet_0015},
    {"Wave - Snippet 16", WAVEFORM_ARBITRARY, AKWF_snippet_0016},
    {"Wave - Snippet 17", WAVEFORM_ARBITRARY, AKWF_snippet_0017},
    {"Wave - Snippet 18", WAVEFORM_ARBITRARY, AKWF_snippet_0018},
    {"Wave - Snippet 19", WAVEFORM_ARBITRARY, AKWF_snippet_0019},
    {"Wave - Snippet 20", WAVEFORM_ARBITRARY, AKWF_snippet_0020},
    {"Wave - Snippet 21", WAVEFORM_ARBITRARY, AKWF_snippet_0021},
    {"Wave - Snippet 22", WAVEFORM_ARBITRARY, AKWF_snippet_0022},
    {"Wave - Snippet 23", WAVEFORM_ARBITRARY, AKWF_snippet_0023},
    {"Wave - Snippet 24", WAVEFORM_ARBITRARY, AKWF_snippet_0024},
    {"Wave - Snippet 25", WAVEFORM_ARBITRARY, AKWF_snippet_0025},
    {"Wave - Snippet 26", WAVEFORM_ARBITRARY, AKWF_snippet_0026},
    {"Wave - Snippet 27", WAVEFORM_ARBITRARY, AKWF_snippet_0027},
    {"Wave - Snippet 28", WAVEFORM_ARBITRARY, AKWF_snippet_0028},
    {"Wave - Snippet 29", WAVEFORM_ARBITRARY, AKWF_snippet_0029},
    {"Wave - Snippet 30", WAVEFORM_ARBITRARY, AKWF_snippet_0030},
    {"Wave - Snippet 31", WAVEFORM_ARBITRARY, AKWF_snippet_0031},
    {"Wave - Snippet 32", WAVEFORM_ARBITRARY, AKWF_snippet_0032},
    {"Wave - Snippet 33", WAVEFORM_ARBITRARY, AKWF_snippet_0033},
    {"Wave - Snippet 34", WAVEFORM_ARBITRARY, AKWF_snippet_0034},
    {"Wave - Snippet 35", WAVEFORM_ARBITRARY, AKWF_snippet_0035},
    {"Wave - Snippet 36", WAVEFORM_ARBITRARY, AKWF_snippet_0036},
    {"Wave - Snippet 37", WAVEFORM_ARBITRARY, AKWF_snippet_0037},
    {"Wave - Snippet 38", WAVEFORM_ARBITRARY, AKWF_snippet_0038},
    {"Wave - Snippet 39", WAVEFORM_ARBITRARY, AKWF_snippet_0039},
    {"Wave - Snippet 40", WAVEFORM_ARBITRARY, AKWF_snippet_0040},
    {"Wave - Snippet 41", WAVEFORM_ARBITRARY, AKWF_snippet_0041},
    {"Wave - Snippet 42", WAVEFORM_ARBITRARY, AKWF_snippet_0042},
    {"Wave - Snippet 43", WAVEFORM_ARBITRARY, AKWF_snippet_0043},
    {"Wave - Snippet 44", WAVEFORM_ARBITRARY, AKWF_snippet_0044},
    {"Wave - Snippet 45", WAVEFORM_ARBITRARY, AKWF_snippet_0045},
    {"Wave - Snippet 46", WAVEFORM_ARBITRARY, AKWF_snippet_0046},
};

#endif