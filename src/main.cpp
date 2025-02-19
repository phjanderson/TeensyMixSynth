#include <Arduino.h>
#include <EEPROM.h>
#include <USBHost_t36.h>
#include <Audio.h>
#include <MIDI.h>

// #define DEBUG_MIDI_HANDLERS
// #define DEBUG_CPU_USAGE
// #define DISABLE_OSC_RESTART

#include "Constants.h"
#include "MiscUtil.h"
#include "SynthController.h"
#include "Param.h"
#include "Synth.h"
#include "DisplayService.h"

#include <vector>


#if AUDIO_BLOCK_SAMPLES != 16 && !defined DISABLE_AUDIO_BLOCK_SAMPLES_CHECK
    #error AUDIO_BLOCK_SAMPLES is not equal to 16, see instructions in Code.md for updating AUDIO_BLOCK_SAMPLES
#endif

// main entrypoint for initializing the synthesizer and task handling

// hardware serial MIDI for 5 pin DIN MIDI interface
static midi::SerialMIDI<HardwareSerial> serialMIDI1(Serial1);
static midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> hardwareSerialMIDI((midi::SerialMIDI<HardwareSerial>&)serialMIDI1);

// USB host MIDI interface for connecting to the Akai MIDImix
// 3 USB hubs are instantiatied, in case USB hubs are used (some hubs contain multiple sub-hubs internally)
// 2 USB MIDI devices are instantiated, one for the Akai MIDImix, one for an optional USB MIDI keyboard (mostly used for debugging purposes)
static USBHost usbHost;

static USBHub hub1(usbHost);
static USBHub hub2(usbHost);
static USBHub hub3(usbHost);

static MIDIDevice_BigBuffer usbHostMidi1(usbHost);
static MIDIDevice_BigBuffer usbHostMidi2(usbHost);

static std::vector<MIDIDeviceBase *> controllerMidiDevices{{&usbHostMidi1, &usbHostMidi2}};

static SynthController synthController;

/**
 * Setup, called on startup.
 * Initializes the USB host, audio memory and synthesizer.
 */
void setup()
{
    hardwareSerialMIDI.begin();
    USBHost::begin();

    // add a slight delay to wait for the USB host and MIDImix to come online, otherwise the first commands sent to the MIDImix will be lost
    delay(600);

    // wait for Arduino Serial Monitor with a 3 seconds timeout
    // elapsedMillis serialWaitTimer;
    // while (!Serial && serialWaitTimer < 3000);

    Serial.println("Synth test setup!");

    AudioMemory(128);

    synthController.initialize(PARAMS, &controllerMidiDevices, &usbMIDI, &hardwareSerialMIDI);
}

/**
 * Task loop.
 * Invokes task() / read() calls on the synthesizer USB and MIDI devices.
 */
void loop()
{
    #ifdef DEBUG_CPU_USAGE
    elapsedMillis synthControllerTask;
    #endif

    // synthesizer task handling
    synthController.task();

    #ifdef DEBUG_CPU_USAGE
    if (synthControllerTask > 1) {
        Serial.println();
        Serial.print("synthController.task(): ");
        Serial.print(synthControllerTask);
        Serial.println("ms");
    }
    #endif

    #ifdef DEBUG_CPU_USAGE
    elapsedMillis usbHostTask;
    #endif

    // USB host task handling
    USBHost::Task();

    #ifdef DEBUG_CPU_USAGE
    if (usbHostTask > 1) {
        Serial.println();
        Serial.print("USBHost::task(): ");
        Serial.print(usbHostTask);
        Serial.println("ms");
    }
    #endif

    #ifdef DEBUG_CPU_USAGE
    elapsedMillis controllerMidiDevicesRead;
    #endif

    // read and handle incoming controller MIDI
    for (auto &controllerMidiDevice : controllerMidiDevices)
    {
        controllerMidiDevice->read();
    }

    #ifdef DEBUG_CPU_USAGE
    if (controllerMidiDevicesRead > 1) {
        Serial.println();
        Serial.print("controllerMidiDevices->read(): ");
        Serial.print(controllerMidiDevicesRead);
        Serial.println("ms");
    }
    #endif

    #ifdef DEBUG_CPU_USAGE
    elapsedMillis usbMidiRead;
    #endif

    // read and handle incoming USB MIDI
    usbMIDI.read();

    #ifdef DEBUG_CPU_USAGE
    if (usbMidiRead > 1) {
        Serial.println();
        Serial.print("usbMIDI.read(): ");
        Serial.print(usbMidiRead);
        Serial.println("ms");
    }
    #endif

    #ifdef DEBUG_CPU_USAGE
    elapsedMillis hardwareSerialMIDIRead;
    #endif

    // read and handle incoming hardware serial MIDI
    hardwareSerialMIDI.read();

    #ifdef DEBUG_CPU_USAGE
    if (hardwareSerialMIDIRead > 1) {
        Serial.println();
        Serial.print("hardwareSerialMIDI.read(): ");
        Serial.print(hardwareSerialMIDIRead);
        Serial.println("ms");
    }
    #endif
}
