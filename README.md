# TeensyMix Synth

TeensyMix synth is an 8-voice polyphonic synthesizer based on the [Teensy 4.1 development board](https://www.pjrc.com/store/teensy41.html).
It is designed to be an easy build with just an LCD display and a digital to analog converter. An [Akai MIDImix](https://www.akaipro.com/midimix) is used to control the synthesizer.
The MIDImix is a compact and affordable MIDI based mixing controller with 24 dials, 9 sliders and 19 buttons with LEDs.

All sound parameters of the synthesizer can be controlled directly using these dials, sliders and buttons. No complicated menus and pages of parameters to scroll through!

[See and listen to what it looks and sounds like!](https://youtu.be/ybsHHy0fLmc)

Features:
- 8-voices with sawtooth, square, sine, triangle, sample & hold noise and several sampled waveforms
- 2 oscillators per voice, one with waveform shape modulation, one with frequency modulation (FM)
- Oscillator 1 supports unison detune with a total of 7 stereo panned oscillators with adjustable detune and mix levels
- 2 12db filters, individually controllable, one with adjustable resonance, allows various combinations of low-pass and high-pass
- 2 envelope generators, one for amplitude, one for modulating the filter, shape, etc
- 1 LFO for modulating the frequency, filter, shape, etc
- Per voice wavefolder for manipulating the waveform
- Per voice waveshaper for distortion
- Stereo ensemble chorus
- Stereo audio using a 24 bit digital to analog converter
- MIDI over USB
- Optional: (5 pin DIN) serial MIDI

For more information about the hardware and schematics, see: [Hardware.md](Hardware.md)

For more information about the source code, see: [Code.md](Code.md)

___Please note:__ this project overclocks the Teensy 4.1 slightly, see [platformio.ini](platformio.ini) for more information._

## Usage

### MIDImix controls

To load a patch:
- press _BANK LEFT_ to enter patch selection mode, the button LED will start to blink slowly
- press _MUTE_ of channel 1 to 8 to select the first digit of the patch to load, the LED will light up
- press _REC ARM_ of channel 1 to 8 to select the second digit of the patch to load, the LED will light up
- the patch is loaded
- you can switch to another patch by selecting another digit using the _MUTE_ or _REC ARM_ buttons
- you can leave patch selection by pressing the _BANK LEFT_ button, the button LEDs of both _BANK LEFT_ and _BANK LEFT_ will turn on (without blinking)
- changing any slider or dial while in patch selection mode will also leave patch selection mode

All patch parameter values will be sent out to external MIDI whenever a patch is loaded. It is possible to record these parameter values using your DAW so your song contains the right parameter values regardless of what the patch is set to.

To save a patch:
- press _BANK RIGHT_ to enter patch save mode, the button LED will start to blink slowly
- the first and second digits of the current patch are indicated using the button LEDs of the _MUTE_ and _REC ARM_ buttons
- optionally press _MUTE_ of channel 1 to 8 to select the first digit of the patch location to save to, the LED will light up
- optionally press _REC ARM_ of channel 1 to 8 to select the second digit of the patch location to save to, the LED will light up
- press _BANK RIGHT_ again to enter patch name mode, the button LED will start to blink quickly
- you can use the _MUTE_ and _REC ARM_ buttons to change the letters 1 to 8 of the patch name
- press _BANK RIGHT_ again to save the patch, the button LEDs of both _BANK LEFT_ and _BANK LEFT_ will turn on (without blinking)
- changing any slider or dial while in patch save / name mode will leave without saving

All other dials, sliders and buttons are directly linked parameters of the synthesizer during play mode. The _MUTE_ and _REC ARM_ buttons are used to increment / decrement parameter values. Keeping _MUTE_ or _REC ARM_ buttons pressed will make them repeat (first slow, then fast).

The display will show the parameter name and value whenever you adjust a parameter value. These values will also be sent out on the external MIDI, so you can record value changes in your song.

Check [control_map.xlsx](control_map.xlsx) to see which dials, sliders and buttons are linked to which parameter.

A few additional parameters such as keyboard tracking can be accessed through menu parameters.

To access the menu parameters:
- press _SOLO_ to enter menu mode
- press the _MUTE_ or _REC ARM_ buttons to select the menu parameter (only a few are currently in use)
- use the _MASTER_ slider to adjust the parameter value
- press _SOLO_ to exit menu mode

### Control changes

The following control changes are accepted on the external USB and 5 pin DIN MIDI:

| Parameter                   |  CC |
| :------------------------- | --: |
| ENV_1_ATTACK               |  73 |
| ENV_1_DECAY                |  75 |
| ENV_1_SUSTAIN              |  79 |
| ENV_1_RELEASE              |  72 |
| ENV_2_ATTACK               |  16 |
| ENV_2_DECAY                |  17 |
| ENV_2_SUSTAIN              |  18 |
| ENV_2_RELEASE              |  19 |
| FILTER_1_FREQ              |  74 |
| FILTER_1_RES               |  71 |
| FILTER_1_KBD_TRACK         |  20 |
| FILTER_1_KBD_VELOCITY      |  21 |
| FILTER_1_ENV_2             |  22 |
| FILTER_1_LFO               |  23 |
| FILTER_MODE                |  24 |
| LFO_FREQ                   |  76 |
| LFO_SHAPE                  |  25 |
| LFO_WAVEFORM               |  26 |
| LFO_ATTACK                 |  78 |
| OSC_1_WAVEFORM             |  27 |
| OSC_1_WAVEFOLD             |  28 |
| OSC_1_SHAPE                |  29 |
| OSC_1_TRANSPOSE            |  30 |
| OSC_1_DETUNE               |  31 |
| OSC_1_MOD_FREQ_ENV_2       |  80 |
| OSC_1_MOD_FREQ_LFO         |  81 |
| OSC_1_MOD_SHAPE_ENV_2      |  82 |
| OSC_1_MOD_SHAPE_LFO        |  83 |
| OSC_1_MOD_WAVEFOLD_ENV_2   |  85 |
| OSC_1_UNISON_DETUNE        |  86 |
| OSC_1_UNISON_MIX           |  87 |
| OSC_FM_WAVEFORM            |  88 |
| OSC_FM_OCTAVE              |  89 |
| OSC_FM_TRANSPOSE           |  90 |
| OSC_FM_MOD_PHASE_MOD_ENV_2 | 102 |
| OSC_FM_PHASE_MOD           | 103 |
| FILTER_2_FREQ_OFFSET       |  81 |
| WAVESHAPE_LEVEL            | 104 |
| PITCH_CHANGE_RANGE_LEVEL   | 105 |
| OSC_VOLUME_MIX             | 106 |
| ENSEMBLE_MIX               |  93 |
| ENSEMBLE_LFO_RATE          |  94 |
| AMP_MOD_LFO                |  92 |
| AMP_KBD_VELOCITY           |  95 |
| MOD_WHL_ENV_REVERSE        | 107 |

_This chart is generated using [generate_external_midi_control_chart.py](src/generate_external_midi_control_chart.py). Regenerate and replace this chart whenever you change external MIDI control changes in [src/ConstantValues.h](src/ConstantValues.h)_

### Program changes

The TeensyMix Synth uses patch number with two digits each containing a number between 1 and 8. The corresponding MIDI program number is shown on the display after the → symbol.

The follow table shows the mappings from MIDI programs to patch numbers:

| Program | Patch |
| :----: | :----: |
|   1    |   11   |
|   2    |   12   |
|   3    |   13   |
|   4    |   14   |
|   5    |   15   |
|   6    |   16   |
|   7    |   17   |
|   8    |   18   |
|   9    |   21   |
|   10   |   22   |
|   11   |   23   |
|   12   |   24   |
|   13   |   25   |
|   14   |   26   |
|   15   |   27   |
|   16   |   28   |
|   17   |   31   |
|   18   |   32   |
|   19   |   33   |
|   20   |   34   |
|   21   |   35   |
|   22   |   36   |
|   23   |   37   |
|   24   |   38   |
|   25   |   41   |
|   26   |   42   |
|   27   |   43   |
|   28   |   44   |
|   29   |   45   |
|   30   |   46   |
|   31   |   47   |
|   32   |   48   |
|   33   |   51   |
|   34   |   52   |
|   35   |   53   |
|   36   |   54   |
|   37   |   55   |
|   38   |   56   |
|   39   |   57   |
|   40   |   58   |
|   41   |   61   |
|   42   |   62   |
|   43   |   63   |
|   44   |   64   |
|   45   |   65   |
|   46   |   66   |
|   47   |   67   |
|   48   |   68   |
|   49   |   71   |
|   50   |   72   |
|   51   |   73   |
|   52   |   74   |
|   53   |   75   |
|   54   |   76   |
|   55   |   77   |
|   56   |   78   |
|   57   |   81   |
|   58   |   82   |
|   59   |   83   |
|   60   |   84   |
|   61   |   85   |
|   62   |   86   |
|   63   |   87   |
|   64   |   88   |

