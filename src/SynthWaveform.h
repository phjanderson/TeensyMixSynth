#ifndef SynthWaveform_h
#define SynthWaveform_h

#include <string>
#include <stdint.h>

/**
 * Synthesizer waveform, used for oscillators and LFOs.
 * Can reference either a standard Teensy Audio waveform or custom 256 samples waveform.
 */
struct SynthWaveform
{
public:
    const std::string name;
    const short audioWaveform;
    const int16_t *waveFormArray;
};

#endif