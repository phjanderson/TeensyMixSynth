#ifndef SynthController_h
#define SynthController_h

#include "fnptr.h"
#include "MiscUtil.h"
#include "DisplayService.h"
#include "Synth.h"
#include "Param.h"
#include "Patch.h"
#include "PatchService.h"
#include <vector>
#include <map>
#include <Metro.h>

/**
 * The SynthController is at the heart of the synthesizer. It handles incoming MIDI messages, translating MIDImix notes and control changes into parameter changes in the synthesizer, handles action buttons such as load and save, sends information to the display, etc. 
 */
class SynthController
{
private:
    // MIDI channel used for sending out messages on the external MIDI
    const static uint8_t MIDI_OUT_CHANNEL = 1;
    // MIDI control change for (pedal) sustain
    const static uint8_t MIDI_CC_SUSTAIN = 64;
    // MIDI control change for modulation wheel
    const static uint8_t MIDI_CC_MOD_WHL = 1;
    // maximum MIDI note, used to prevent excessive CPU usage, the CPU usage of AudioSynthWaveformModulated increases as the frequency increases
    const static uint8_t MIDI_NOTE_MAX = 96;
    // highest note sent out by the MIDImix, used to separate notes and button presses on incoming controller MIDI messages
    const static uint8_t CONTROL_NOTE_MAX = 27;

    // state machine, start in play state
    enum class State { play, loadSelect, saveSelect, saveName, menu };
    State state = State::play;
    
    // selected digits for load and save, 0 = not digit selected yet
    uint8_t patchSelectDigit1 = 0;
    uint8_t patchSelectDigit2 = 0;

    // control state light states
    enum class LightState { off, on, blinkSlow, blinkFast };
    bool controlStateLightLoadWasOn{false};
    LightState controlStateLightLoadState{LightState::off};
    bool controlStateLightSaveWasOn{false};
    LightState controlStateLightSaveState{LightState::off};

    // USB host MIDI devices, MIDImix and additional devices such as a keyboard (when using a USB hub)
    std::vector<MIDIDeviceBase *> * usbHostMidiDevices;
    // external USB MIDI (DAW)
    usb_midi_class * extMidiUsb;
    // external hardware serial MIDI (DAW)
    midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * extMidiHardwareSerial;

    // current patch
    Patch currentPatch{"Init"};
    // current patch number
    uint8_t currentPatchNumber{0};

    // current menu param ID
    uint8_t currentMenuParamId{0};

    // parameter ID to param mappings
    std::map<uint16_t, const Param *> paramMap;
    // external MIDI control change to param mappings
    std::map<uint8_t, const Param *> midiCcParamMap;
    // controller MIDI control change to param mappings
    std::map<uint8_t, const Param *> controllerCcParamMap;
    // controller MIDI increment button note to param mappings
    std::map<uint8_t, const Param *> controllerNiParamMap;
    // controller MIDI decrement button note to param mappings
    std::map<uint8_t, const Param *> controllerNdParamMap;
    // menu param ID to param mappings
    std::map<uint8_t, const Param *> menuIdParamMap;
    
    // increment/decrement button repeat
    // delay in milliseconds
    const static uint16_t buttonRepeatDelayMillis{1000};
    // fast repeat in milliseconds
    Metro niNdButtonRepeatStateMetro = Metro(50);
    // delay before fast repeat starts
    const static uint16_t buttonRepeatFastDelayMillis{5000};
    // divider for slow repeat
    const static uint8_t BUTTON_REPEAT_SLOW_MODULUS{5};
    uint32_t buttonRepeatMetroCounter{0L};
    uint8_t lastNiNdNote{0};
    bool niNdButtonPressed{false};
    elapsedMillis elapsedMillisSinceLastNiNdButtonPress;

    // instances
    Synth synth;
    DisplayService displayService;
    PatchService patchService;

    #ifdef DEBUG_CPU_USAGE
    // log CPU statistics every x milliseconds
    Metro cpuMetro = Metro(2000);
    #endif

    // update the display every x milliseconds
    Metro displayMetro = Metro(200);

    // blink control state lights
    Metro lightStateMetro = Metro(125);
    uint32_t lightStateMetroCounter{0L};
    const static uint8_t LIGHT_STATE_BLINK_SLOW_MODULUS{4};

    // decrement button pressed states
    std::array<bool, 8> controlValueDecrementPressed{false};

    /**
     * Send a note on to the controller. Used for controlling button lights.
     * 
     * @param note note
     * @param velocity velocity
     * @param channel channel
     * @param cable cable (defaults to 0)
     */
    void sendNoteOnToController(uint8_t note, uint8_t velocity, uint8_t channel, uint8_t cable = 0)
    {
        #ifdef DEBUG_MIDI_HANDLERS
        Serial.print("Sending Note On to controller, ch=");
        Serial.print(channel);
        Serial.print(", note=");
        Serial.print(note);
        Serial.print(", velocity=");
        Serial.print(velocity);
        Serial.println();
        #endif

        for (auto &usbHostMidiDevice : *usbHostMidiDevices)
        {
            if (isAkaiMidiMix(usbHostMidiDevice))
            {
                usbHostMidiDevice->sendNoteOn(note, velocity, channel, cable);
            }
        }
    }

    /**
     * Send a control change to external MIDI (USB and hardware serial).
     * 
     * @param control control
     * @param value value
     * @param channel channel
     */
    void sendControlChangeToExtMidi(uint8_t control, uint8_t value, uint8_t channel)
    {
        #ifdef DEBUG_MIDI_HANDLERS
        Serial.print("Sending Control Change to ext MIDI, ch=");
        Serial.print(channel);
        Serial.print(", control=");
        Serial.print(control);
        Serial.print(", value=");
        Serial.print(value);
        Serial.println();
        #endif

        extMidiUsb->sendControlChange(control, value, channel);
        extMidiHardwareSerial->sendControlChange(control, value, channel);
    }

    /**
     * Send a program change to external MIDI (USB and hardware serial).
     * 
     * @param program program
     * @param channel channel
     */
    void sendProgramChangeToExtMidi(uint8_t program, uint8_t channel)
    {
        #ifdef DEBUG_MIDI_HANDLERS
        Serial.print("Sending Program Change to ext MIDI, ch=");
        Serial.print(channel);
        Serial.print(", program=");
        Serial.print(program);
        Serial.println();
        #endif

        extMidiUsb->sendProgramChange(program, channel);
        extMidiHardwareSerial->sendProgramChange(program, channel);
    }

    /**
     * Convert the current state to a string for display purposes.
     * 
     * @return std::string state string
     */
    std::string currentStateToString()
    {
        switch (state)
        {
        case State::play:
            return std::string("Play");

        case State::loadSelect:
            return std::string("Load");

        case State::saveSelect:
            return std::string("Save");

        case State::saveName:
            return std::string("Name");

        case State::menu:
            return std::string("Menu");

        default:
            return std::string("Play");
        }
    }

    /**
     * Update the display and apply the current patch, sending all parameter values stored in the patch to the synth.
     */
    void applyCurrentPatch()
    {
        // currentPatch.debugPrint();

        displayService.displayPatchNumber(currentPatchNumber);
        displayService.displayPatchName(currentPatch);
        displayService.clearParamNameAndValue();

        for (const auto [paramId, paramValue] : currentPatch.paramValueMap)
        {
            if (!paramMap.count(paramId))
            {
                Serial.printf("Warning: patch contains missing param with paramId %d\n", paramId);
                Serial.printf("Warning: deleting param value with paramId %d\n", paramId);
                currentPatch.deleteParamValue(paramId);
            }
            else
            {
                paramMap.at(paramId)->updateSynth(synth, paramValue);
            }
        }
    }

    /**
     * Handle control changes coming from the external MIDI.
     * 
     * @param control control change
     * @param value value
     * @return bool true if the control change was processed (valid parameter)
     */
    bool handleMidiCc(uint8_t control, uint8_t value)
    {
        if (midiCcParamMap.count(control))
        {
            auto param = midiCcParamMap.at(control);

            // do not process if the value is equal to the current value
            if (value != currentPatch.getParamValue(param->getParamId()))
            {
                // update the current patch
                value = currentPatch.setParamValue(param->getParamId(), value, param->getMaxValue());

                // update the synth
                param->updateSynth(synth, value);

                // update the display
                // displayService.displayParamNameAndValue(*param, value);
            }

            return true;
        }

        return false;
    }

    /**
     * Handle control changes coming from the controller MIDI.
     * 
     * @param control control change
     * @param value value
     * @return bool true if the control change was processed (valid parameter)
     */
    bool handleControllerCc(uint8_t control, uint8_t value)
    {
        // touching any (dial/slider) control while in load or save state will return the synth to play state
        if (state == State::loadSelect || state == State::saveSelect || state == State::saveName)
        {
            enterStatePlay();
        }

        // handle master slider for menu params
        if (state == State::menu && control == MIDIMIX_MASTER_SLIDER_CC)
        {
            if (menuIdParamMap.count(currentMenuParamId))
            {
                auto param = menuIdParamMap.at(currentMenuParamId);

                // update the current patch
                value = currentPatch.setParamValue(param->getParamId(), value, param->getMaxValue());

                // update the synth
                param->updateSynth(synth, value);

                // update the display
                displayService.displayParamNameAndValue(*param, value);

                // send a control change to the external MIDI, if a MIDI control change is configured
                if (param->getMidiCc() <= 127)
                {
                    sendControlChangeToExtMidi(param->getMidiCc(), value, MIDI_OUT_CHANNEL);
                }
            }

            return true;
        }

        // handle control params
        if (controllerCcParamMap.count(control))
        {
            auto param = controllerCcParamMap.at(control);

            // do not process if the value is equal to the current value
            if (value != currentPatch.getParamValue(param->getParamId()))
            {
                // update the current patch
                value = currentPatch.setParamValue(param->getParamId(), value, param->getMaxValue());

                // update the synth
                param->updateSynth(synth, value);

                // update the display
                displayService.displayParamNameAndValue(*param, value);

                // send a control change to the external MIDI, if a MIDI control change is configured
                if (param->getMidiCc() <= 127)
                {
                    sendControlChangeToExtMidi(param->getMidiCc(), value, MIDI_OUT_CHANNEL);
                }
            }

            return true;
        }

        return false;
    }

    /**
     * Handle note on messages coming from the controller MIDI.
     * 
     * @param note note
     * @return bool true if the note was processed (valid parameter)
     */
    bool handleControllerNoteOn(uint8_t note)
    {
        // check if all decrement buttons are pressed at the same time, if yes, then delete all patches
        if (CONTROL_ND_VALUE_MAP.count(note))
        {
            controlValueDecrementPressed[CONTROL_ND_VALUE_MAP.at(note) - 1] = true;

            bool allControlValueDecrementPressed = true;
            for (auto pressed : controlValueDecrementPressed)
            {
                if (!pressed)
                {
                    allControlValueDecrementPressed = false;
                    break;
                }
            }
            if (allControlValueDecrementPressed)
            {
                //TODO: remove or add confirmation?
                Serial.println("All control value decrement buttons pressed simultaneously, deleting all patches");
                patchService.deleteAllPatches();
                // patchService.copyAllPatchesToSd();

                currentPatch = patchService.initPatch();
                applyCurrentPatch();
                
                return true;
            }
        }

        // keep track of increment and decrement button presses for button repeat purposes
        if (CONTROL_NI_VALUE_MAP.count(note) || CONTROL_ND_VALUE_MAP.count(note))
        {
            if (!niNdButtonPressed)
            {
                elapsedMillisSinceLastNiNdButtonPress = elapsedMillis();
            }
            lastNiNdNote = note;
            niNdButtonPressed = true;
        }

        // menu state
        if (state == State::menu)
        {
            // pressing the menu button returns to play state
            if (note == CONTROL_NT_MENU)
            {
                enterStatePlay();
                return true;
            }

            // increment and decrement buttons select the two digits of the menu param
            if (CONTROL_NI_VALUE_MAP.count(note))
            {
                // note increment buttons access menu params 0 - 7
                currentMenuParamId = CONTROL_NI_VALUE_MAP.at(note) - 1;

                // select the menu param
                onMenuParamSelect();

                return true;
            }
            if (CONTROL_ND_VALUE_MAP.count(note))
            {
                // note increment buttons access menu params 8 - 15
                currentMenuParamId = CONTROL_ND_VALUE_MAP.at(note) + 7;

                // select the menu param
                onMenuParamSelect();

                return true;
            }
        }

        // load select state
        if (state == State::loadSelect)
        {
            // pressing the load button again returns to play state
            if (note == CONTROL_NT_LOAD)
            {
                enterStatePlay();
                return true;
            }

            // increment and decrement buttons select the two digits of the patch
            if (CONTROL_NI_VALUE_MAP.count(note))
            {
                onPatchSelectDigit1(CONTROL_NI_VALUE_MAP.at(note));

                if (patchSelectDigit1 > 0 && patchSelectDigit2 > 0)
                {
                    // load the patch if both digits are selected
                    onPatchLoadSelect();
                }

                return true;
            }
            if (CONTROL_ND_VALUE_MAP.count(note))
            {
                onPatchSelectDigit2(CONTROL_ND_VALUE_MAP.at(note));

                if (patchSelectDigit1 > 0 && patchSelectDigit2 > 0)
                {
                    // load the patch if both digits are selected
                    onPatchLoadSelect();
                }

                return true;
            }
        }

        // save select state
        if (state == State::saveSelect)
        {
            // pressing the save button again switches to save name state
            if (note == CONTROL_NT_SAVE)
            {
                enterStateSaveName();
                return true;
            }

            // pressing the load or menu control buttons returns to play state
            if (note == CONTROL_NT_LOAD || note == CONTROL_NT_MENU)
            {
                enterStatePlay();
                return true;
            }

            // increment and decrement buttons select the two digits of the patch
            if (CONTROL_NI_VALUE_MAP.count(note))
            {
                onPatchSelectDigit1(CONTROL_NI_VALUE_MAP.at(note));
                displayService.displayPatchNumber(convertPatchDigitsToNumber(patchSelectDigit1, patchSelectDigit2));
                return true;
            }
            if (CONTROL_ND_VALUE_MAP.count(note))
            {
                onPatchSelectDigit2(CONTROL_ND_VALUE_MAP.at(note));
                displayService.displayPatchNumber(convertPatchDigitsToNumber(patchSelectDigit1, patchSelectDigit2));
                return true;
            }
        }

        // save name state
        if (state == State::saveName)
        {
            // pressing the save button confirms the save action
            if (note == CONTROL_NT_SAVE)
            {
                onPatchSaveConfirm();

                // return to play state
                enterStatePlay();
                return true;
            }

            // pressing the increment buttons increments the letter at that position
            if (CONTROL_NI_VALUE_MAP.count(note))
            {
                currentPatch.incrementNameLetter(CONTROL_NI_VALUE_MAP.at(note) - 1);
                displayService.displayPatchName(currentPatch);

                return true;
            }
            // pressing the decrement buttons decrements the letter at that position
            if (CONTROL_ND_VALUE_MAP.count(note))
            {
                currentPatch.decrementNameLetter(CONTROL_ND_VALUE_MAP.at(note) - 1);
                displayService.displayPatchName(currentPatch);

                return true;
            }
        }

        // load button switches to load select state
        if (note == CONTROL_NT_LOAD)
        {
            // first go through play state to reset the display
            enterStatePlay();

            enterStateLoadSelect();
            return true;
        }

        // save button switches to save select state
        if (note == CONTROL_NT_SAVE)
        {
            // first go through play state to reset the display
            enterStatePlay();

            enterStateSaveSelect();
            return true;
        }

        // menu button switches to menu state
        if (note == CONTROL_NT_MENU)
        {
            // first go through play state to reset the display
            enterStatePlay();

            enterStateMenu();
            return true;
        }

        // touching any other control while in load or save state will return the synth to play state
        if (note <= CONTROL_NOTE_MAX && (state == State::loadSelect || state == State::saveSelect || state == State::saveName))
        {
            enterStatePlay();
        }

        // check if an increment or decrement button was pressed
        int8_t incrementValue = 0;
        if (controllerNiParamMap.count(note))
        {
            incrementValue = 1;
        }
        else if (controllerNdParamMap.count(note))
        {
            incrementValue = -1;
        }

        if (incrementValue != 0)
        {
            // fetch the param
            auto param = incrementValue > 0 ? controllerNiParamMap.at(note) : controllerNdParamMap.at(note);

            // update the current patch
            uint8_t value = currentPatch.incrementParamValue(param->getParamId(), incrementValue, param->getMaxValue());

            // update the synth
            param->updateSynth(synth, value);

            // update the display
            displayService.displayParamNameAndValue(*param, value);

            // send a control change to the external MIDI, if a MIDI control change is configured
            if (param->getMidiCc() <= 127)
            {
                sendControlChangeToExtMidi(param->getMidiCc(), value, MIDI_OUT_CHANNEL);
            }

            return true;
        }

        return false;
    }

    /**
     * Handle note off messages coming from the controller MIDI.
     * 
     * @param note note
     * @return bool true if the note was processed (valid parameter)
     */
    bool handleControllerNoteOff(uint8_t note)
    {
        // keep track of pressed decrement buttons
        if (CONTROL_ND_VALUE_MAP.count(note))
        {
            controlValueDecrementPressed[CONTROL_ND_VALUE_MAP.at(note) - 1] = false;
        }

        // keep track of increment and decrement button releases for button repeat purposes
        if (CONTROL_NI_VALUE_MAP.count(note) || CONTROL_ND_VALUE_MAP.count(note))
        {
            niNdButtonPressed = false;
        }

        return false;
    }

    /**
     * Set the control state light "load".
     * 
     * Please note: do not use directly use setControlStateLightLoadLightState() instead
     * 
     * @param on on if true
     */
    void setControlStateLightLoad(bool on)
    {
        sendNoteOnToController(CONTROL_NT_LOAD, on ? 127 : 0, 1);
        controlStateLightLoadWasOn = on;
    }

    /**
     * Set the control state light "save".
     * 
     * Please note: do not use directly use setControlStateLightSaveLightState() instead
     * 
     * @param on on if true
     */
    void setControlStateLightSave(bool on)
    {
        sendNoteOnToController(CONTROL_NT_SAVE, on ? 127 : 0, 1);
        controlStateLightSaveWasOn = on;
    }

    /**
     * Set the control state light "load" light state.
     * 
     * @param lightState light state
     */
    void setControlStateLightLoadLightState(LightState lightState)
    {
        controlStateLightLoadState = lightState;
        
        // process on/off directly and start blink with on
        if (lightState == LightState::off)
        {
            setControlStateLightLoad(false);
        }
        else
        {
            setControlStateLightLoad(true);
        }
    }

    /**
     * Set the control state light "save" light state.
     * 
     * @param lightState light state
     */
    void setControlStateLightSaveLightState(LightState lightState)
    {
        controlStateLightSaveState = lightState;

        // process on/off directly and start blink with on
        if (lightState == LightState::off)
        {
            setControlStateLightSave(false);
        }
        else
        {
            setControlStateLightSave(true);
        }
    }

    /**
     * Set the control state light for digit 1.
     * 
     * @param value digit value (1-8)
     * @param on on if true
     */
    void setControlValueLightDigit1(uint8_t value, bool on)
    {
        if (CONTROL_VALUE_NI_MAP.count(value))
        {
            sendNoteOnToController(CONTROL_VALUE_NI_MAP.at(value), on ? 127 : 0, 1);
        }
    }

    /**
     * Set the control state light for digit 2.
     * 
     * @param value digit value (1-8)
     * @param on on if true
     */
    void setControlValueLightDigit2(uint8_t value, bool on)
    {
        if (CONTROL_VALUE_ND_MAP.count(value))
        {
            sendNoteOnToController(CONTROL_VALUE_ND_MAP.at(value), on ? 127 : 0, 1);
        }
    }

    /**
     * Set the control value lights for both digits.
     * 
     * @param digits digits
     * @param on on if true
     */
    void setControlValueLightDigits(uint8_t digits, bool on)
    {
        uint8_t digit1 = digits / 10;
        uint8_t digit2 = digits % 10;

        setControlValueLightDigit1(digit1, on);
        setControlValueLightDigit2(digit2, on);
    }

    /**
     * Set all control state lights light state.
     * 
     * @param lightState light state
     */
    void setAllControlStateLightsLightState(LightState lightState)
    {
        setControlStateLightLoadLightState(lightState);
        setControlStateLightSaveLightState(lightState);
    }

    /**
     * Set all control value lights.
     * 
     * @param on on if true
     */
    void setAllControlValueLights(bool on)
    {
        for (uint8_t value = 1 ; value <= 8 ; value++)
        {
            setControlValueLightDigit1(value, on);
            setControlValueLightDigit2(value, on);
        }
    }

    /**
     * Enter play state.
     */
    void enterStatePlay()
    {
        Serial.println("Entering state: play");

        setAllControlStateLightsLightState(LightState::off);
        setAllControlValueLights(false);

        state = State::play;
        patchSelectDigit1 = 0;
        patchSelectDigit2 = 0;

        setControlStateLightLoadLightState(LightState::on);
        setControlStateLightSaveLightState(LightState::on);

        displayService.displayState(currentStateToString());
        displayService.displayPatchName(currentPatch);
        displayService.displayPatchNumber(currentPatchNumber);
        displayService.clearParamNameAndValue();
    }

    /**
     * Enter load select state.
     */
    void enterStateMenu()
    {
        Serial.println("Entering state: menu");

        setAllControlStateLightsLightState(LightState::off);
        setAllControlValueLights(false);

        state = State::menu;
        patchSelectDigit1 = 0;
        patchSelectDigit2 = 0;

        setControlStateLightLoadLightState(LightState::blinkSlow);
        setControlStateLightSaveLightState(LightState::blinkSlow);

        displayService.displayState(currentStateToString());
        displayService.clearParamNameAndValue();
    }

    /**
     * Enter load select state.
     */
    void enterStateLoadSelect()
    {
        Serial.println("Entering state: loadSelect");

        setAllControlStateLightsLightState(LightState::off);
        setAllControlValueLights(false);

        state = State::loadSelect;
        patchSelectDigit1 = 0;
        patchSelectDigit2 = 0;

        setControlStateLightLoadLightState(LightState::blinkSlow);

        displayService.displayState(currentStateToString());
        displayService.clearParamNameAndValue();
    }

    /**
     * Enter save select state.
     */
    void enterStateSaveSelect()
    {
        Serial.println("Entering state: saveSelect");

        setAllControlStateLightsLightState(LightState::off);
        setAllControlValueLights(false);

        state = State::saveSelect;
        uint8_t patchDigits = convertPatchNumberToDigits(currentPatchNumber);
        patchSelectDigit1 = patchDigits / 10;
        patchSelectDigit2 = patchDigits % 10;
        setControlValueLightDigits(patchDigits, true);

        setControlStateLightSaveLightState(LightState::blinkSlow);

        displayService.displayState(currentStateToString());
        displayService.clearParamNameAndValue();
    }

    /**
     * Enter save name state.
     */
    void enterStateSaveName()
    {
        Serial.println("Entering state: saveName");

        setAllControlStateLightsLightState(LightState::off);
        setAllControlValueLights(true);

        state = State::saveName;

        setControlStateLightSaveLightState(LightState::blinkFast);

        displayService.displayState(currentStateToString());
        displayService.displayPatchNameEditNumbers();
    }

    /**
     * Patch select digit 1 handler.
     * 
     * @param value digit value (1-8)
     */
    void onPatchSelectDigit1(uint8_t value)
    {
        if (patchSelectDigit1 > 0)
        {
            setControlValueLightDigit1(patchSelectDigit1, false);
        }
        patchSelectDigit1 = value;

        setControlValueLightDigit1(value, true);
    }

    /**
     * Patch select digit 2 handler.
     * 
     * @param value digit value (1-8)
     */
    void onPatchSelectDigit2(uint8_t value)
    {
        if (patchSelectDigit2 > 0)
        {
            setControlValueLightDigit2(patchSelectDigit2, false);
        }
        patchSelectDigit2 = value;

        setControlValueLightDigit2(value, true);
    }

    /**
     * Patch load select handler.
     */
    void onPatchLoadSelect()
    {
        currentPatchNumber = convertPatchDigitsToNumber(patchSelectDigit1, patchSelectDigit2);

        Serial.print("Loading patch: ");
        Serial.print(currentPatchNumber);
        Serial.println();

        currentPatch = patchService.loadPatch(currentPatchNumber);

        applyCurrentPatch();

        // send a program change to external MIDI
        sendProgramChangeToExtMidi(currentPatchNumber, MIDI_OUT_CHANNEL);
    }

    /**
     * Patch save confirm handler.
     */
    void onPatchSaveConfirm()
    {
        currentPatchNumber = convertPatchDigitsToNumber(patchSelectDigit1, patchSelectDigit2);

        Serial.print("Saving patch: ");
        Serial.print(currentPatchNumber);
        Serial.println();

        patchService.savePatch(currentPatchNumber, currentPatch);

        // send a program change to external MIDI
        sendProgramChangeToExtMidi(currentPatchNumber, MIDI_OUT_CHANNEL);

        displayService.clearPatchNameEditNumbers();
    }

    /**
     * Menu param select handler.
     */
    void onMenuParamSelect()
    {
        setAllControlValueLights(false);
        
        if (currentMenuParamId < 8)
        {
            setControlValueLightDigit1(currentMenuParamId + 1, true);
            setControlValueLightDigit2(currentMenuParamId + 1, false);
        }
        else
        {
            setControlValueLightDigit1(currentMenuParamId - 7, false);
            setControlValueLightDigit2(currentMenuParamId - 7, true);
        }

        Serial.print("Selecting menu param with ID: ");
        Serial.print(currentMenuParamId);
        Serial.println();

        if (menuIdParamMap.count(currentMenuParamId))
        {
            auto param = menuIdParamMap.at(currentMenuParamId);

            // display the param name and current value
            displayService.displayParamNameAndValue(*param, currentPatch.getParamValue(param->getParamId()));
        }
    }

    /**
     * MIDI note on handler.
     * 
     * @param channel channel
     * @param note note
     * @param velocity velocity
     * @param controller true if message came from controller MIDI, false if message came from external MIDI
     */
    void onNoteOn(uint8_t channel, uint8_t note, uint8_t velocity, bool controller)
    {
        #ifdef DEBUG_MIDI_HANDLERS
        Serial.print("Note On, ch=");
        Serial.print(channel);
        Serial.print(", note=");
        Serial.print(note);
        Serial.print(", velocity=");
        Serial.print(velocity);
        Serial.print(", controller=");
        Serial.print(controller);
        Serial.println();
        #endif

        // handle the note on as a musical note if it did not originate from controller MIDI or was not handled by the controller logic
        if (!controller || !handleControllerNoteOn(note))
        {
            // limit the highest note, CPU usage of OSC1 increases as the note frequency increases
            if (note <= MIDI_NOTE_MAX)
            {
                synth.onNoteOn(note, velocity);
            }
        }
    }

    /**
     * MIDI note off handler.
     * 
     * @param channel channel
     * @param note note
     * @param controller true if message came from controller MIDI, false if message came from external MIDI
     */
    void onNoteOff(uint8_t channel, uint8_t note, bool controller)
    {
        #ifdef DEBUG_MIDI_HANDLERS
        Serial.print("Note Off, ch=");
        Serial.print(channel);
        Serial.print(", note=");
        Serial.print(note);
        Serial.print(", controller=");
        Serial.print(controller);
        Serial.println();
        #endif

        // handle the note off as a musical note if it did not originate from controller MIDI or was not handled by the controller logic
        if (!controller || !handleControllerNoteOff(note))
        {
            synth.onNoteOff(note);
        }
    }

    /**
     * MIDI control change handler.
     * 
     * @param channel channel
     * @param control control change
     * @param value value
     * @param controller true if message came from controller MIDI, false if message came from external MIDI
     */
    void onControlChange(uint8_t channel, uint8_t control, uint8_t value, bool controller)
    {
        #ifdef DEBUG_MIDI_HANDLERS
        Serial.print("Control Change, ch=");
        Serial.print(channel);
        Serial.print(", control=");
        Serial.print(control);
        Serial.print(", value=");
        Serial.print(value);
        Serial.print(", controller=");
        Serial.print(controller);
        Serial.println();
        #endif

        // is it (pedal) sustain?
        if (control == MIDI_CC_SUSTAIN)
        {
            synth.onSustainToggle(value >= 64);
            return;
        }

        // is it modulation wheel?
        if (control == MIDI_CC_MOD_WHL)
        {
            synth.setModWhl((float)value / 127.0f);
            return;
        }

        // otherwise send it to controller MIDI or external MIDI control change handler
        if (controller)
        {
            handleControllerCc(control, value);
        }
        else
        {
            handleMidiCc(control, value);
        }
    }

    /**
     * Pitch change handler.
     * 
     * @param channel channel
     * @param pitch pitch
     * @param controller true if message came from controller MIDI, false if message came from external MIDI
     */
    void onPitchChange(uint8_t channel, int pitch, bool controller)
    {
        #ifdef DEBUG_MIDI_HANDLERS
        Serial.print("Pitch Bend, ch=");
        Serial.print(channel);
        Serial.print(", value=");
        Serial.print(pitch);
        Serial.print(", controller=");
        Serial.print(controller);
        Serial.println();
        #endif

        if (pitch > 0)
        {
            synth.setPitchChange((float)pitch / 8191.0f);
        }
        else
        {
            synth.setPitchChange((float)pitch / 8192.0f);
        }
    }

    /**
     * Program change handler.
     * 
     * @param channel channel
     * @param program program
     * @param controller true if message came from controller MIDI, false if message came from external MIDI
     */
    void onProgramChange(uint8_t channel, uint8_t program, bool controller)
    {
        #ifdef DEBUG_MIDI_HANDLERS
        Serial.print("Program Change, ch=");
        Serial.print(channel);
        Serial.print(", value=");
        Serial.print(program);
        Serial.print(", controller=");
        Serial.print(controller);
        Serial.println();
        #endif

        // do not process if the program is greater than 63 or equal to the current patch number
        if (program <=63 && program != currentPatchNumber)
        {
            currentPatchNumber = program;
            currentPatch = patchService.loadPatch(currentPatchNumber);
            applyCurrentPatch();

            enterStatePlay();

            if (controller)
            {
                // send a program change to external MIDI if the program change came from the controller MIDI
                sendProgramChangeToExtMidi(currentPatchNumber, MIDI_OUT_CHANNEL);
            }
        }
    }

public:
    /**
     * Initialize the synth controller.
     * 
     * @param params reference to the param list
     * @param usbHostMidiDevices USB host MIDI devices
     * @param extMidiUsb external USB MIDI 
     * @param extMidiHardwareSerial external hardware serial MIDI
     */
    void initialize(const std::vector<Param> &params, std::vector<MIDIDeviceBase *> * usbHostMidiDevices, usb_midi_class * extMidiUsb, midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> * extMidiHardwareSerial)
    {
        this->usbHostMidiDevices = usbHostMidiDevices;
        this->extMidiUsb = extMidiUsb;
        this->extMidiHardwareSerial = extMidiHardwareSerial;

        setAllControlStateLightsLightState(LightState::off);
        setAllControlValueLights(false);

        // create mappings
        for (auto &param : params)
        {
            if (paramMap.count(param.getParamId()))
            {
                Serial.printf("Warning: duplicate paramId %d found, ignoring duplicate param\n", param.getParamId());
            }
            else
            {
                paramMap[param.getParamId()] = &param;
                if (param.getMidiCc() <= 127)
                {
                    midiCcParamMap[param.getMidiCc()] = &param;
                }
                if (param.getControllerCc() <= 127)
                {
                    controllerCcParamMap[param.getControllerCc()] = &param;
                }
                if (param.getControllerNi() <= 127)
                {
                    controllerNiParamMap[param.getControllerNi()] = &param;
                }
                if (param.getControllerNd() <= 127)
                {
                    controllerNdParamMap[param.getControllerNd()] = &param;
                }
                if (param.getMenuId() <= 127)
                {
                    menuIdParamMap[param.getMenuId()] = &param;
                }
            }
        }

        // initialize dependencies
        synth.initialize();
        displayService.initialize();
        patchService.initialize(&paramMap, &displayService);

        // load patch 0
        currentPatch = patchService.loadPatch(currentPatchNumber);
        applyCurrentPatch();

        // enter play state
        enterStatePlay();

        // register MIDI handlers for USB host MIDI devices
        // use fnptr to wrap reference to method calls on this SynthController instance to "normal" function pointers
        for (auto &usbHostMidiDevice : *usbHostMidiDevices)
        {
            Serial.print("idVendor: ");
            Serial.println(usbHostMidiDevice->idVendor());
            Serial.print("idProduct: ");
            Serial.println(usbHostMidiDevice->idProduct());

            if (isAkaiMidiMix(usbHostMidiDevice))
            {
                Serial.println("Found AKAI MIDI Mix connected to USB host");

                usbHostMidiDevice->setHandleNoteOn(
                    fnptr<void(uint8_t channel, uint8_t note, uint8_t velocity)>(
                        [this](uint8_t channel, uint8_t note, uint8_t velocity)
                        {
                            this->onNoteOn(channel, note, velocity, true);
                        }
                    )
                );
                usbHostMidiDevice->setHandleNoteOff(
                    fnptr<void(uint8_t channel, uint8_t note, uint8_t velocity)>(
                        [this](uint8_t channel, uint8_t note, [[maybe_unused]] uint8_t velocity)
                        {
                            this->onNoteOff(channel, note, true);
                        }
                    )
                );
                usbHostMidiDevice->setHandleControlChange(
                    fnptr<void(uint8_t channel, uint8_t control, uint8_t value)>(
                        [this](uint8_t channel, uint8_t control, uint8_t value)
                        {
                            this->onControlChange(channel, control, value, true);
                        }
                    )
                );
                usbHostMidiDevice->setHandlePitchChange(
                    fnptr<void(uint8_t channel, int pitch)>(
                        [this](uint8_t channel, int pitch)
                        {
                            this->onPitchChange(channel, pitch, true);
                        }
                    )
                );
                usbHostMidiDevice->setHandleProgramChange(
                    fnptr<void(uint8_t channel, uint8_t program)>(
                        [this](uint8_t channel, uint8_t program)
                        {
                            this->onProgramChange(channel, program, true);
                        }
                    )
                );
            }
            else
            {
                Serial.println("Found other MIDI device connected to USB host");

                usbHostMidiDevice->setHandleNoteOn(
                    fnptr<void(uint8_t channel, uint8_t note, uint8_t velocity)>(
                        [this](uint8_t channel, uint8_t note, uint8_t velocity)
                        {
                            this->onNoteOn(channel, note, velocity, false);
                        }
                    )
                );
                usbHostMidiDevice->setHandleNoteOff(
                    fnptr<void(uint8_t channel, uint8_t note, uint8_t velocity)>(
                        [this](uint8_t channel, uint8_t note, [[maybe_unused]] uint8_t velocity)
                        {
                            this->onNoteOff(channel, note, false);
                        }
                    )
                );
                usbHostMidiDevice->setHandleControlChange(
                    fnptr<void(uint8_t channel, uint8_t control, uint8_t value)>(
                        [this](uint8_t channel, uint8_t control, uint8_t value)
                        {
                            this->onControlChange(channel, control, value, false);
                        }
                    )
                );
                usbHostMidiDevice->setHandlePitchChange(
                    fnptr<void(uint8_t channel, int pitch)>(
                        [this](uint8_t channel, int pitch)
                        {
                            this->onPitchChange(channel, pitch, false);
                        }
                    )
                );
                usbHostMidiDevice->setHandleProgramChange(
                    fnptr<void(uint8_t channel, uint8_t program)>(
                        [this](uint8_t channel, uint8_t program)
                        {
                            this->onProgramChange(channel, program, false);
                        }
                    )
                );
            }
        }

        // register MIDI handlers for external USB MIDI
        // use fnptr to wrap reference to method calls on this SynthController instance to "normal" function pointers
        extMidiUsb->setHandleNoteOn(
            fnptr<void(uint8_t channel, uint8_t note, uint8_t velocity)>(
                [this](uint8_t channel, uint8_t note, uint8_t velocity)
                {
                    this->onNoteOn(channel, note, velocity, false); 
                }
            )
        );
        extMidiUsb->setHandleNoteOff(
            fnptr<void(uint8_t channel, uint8_t note, uint8_t velocity)>(
                [this](uint8_t channel, uint8_t note, [[maybe_unused]] uint8_t velocity)
                {
                    this->onNoteOff(channel, note, false);
                }
            )
        );
        extMidiUsb->setHandleControlChange(
            fnptr<void(uint8_t channel, uint8_t control, uint8_t value)>(
                [this](uint8_t channel, uint8_t control, uint8_t value)
                {
                    this->onControlChange(channel, control, value, false);
                }
            )
        );
        extMidiUsb->setHandlePitchChange(
            fnptr<void(uint8_t channel, int pitch)>(
                [this](uint8_t channel, int pitch)
                {
                    this->onPitchChange(channel, pitch, false);
                }
            )
        );
        extMidiUsb->setHandleProgramChange(
            fnptr<void(uint8_t channel, uint8_t program)>(
                [this](uint8_t channel, uint8_t program)
                {
                    this->onProgramChange(channel, program, false);
                }
            )
        );

        // register MIDI handlers for external hardware serial MIDI
        // use fnptr to wrap reference to method calls on this SynthController instance to "normal" function pointers
        extMidiHardwareSerial->setHandleNoteOn(
            fnptr<void(uint8_t channel, uint8_t note, uint8_t velocity)>(
                [this](uint8_t channel, uint8_t note, uint8_t velocity)
                {
                    this->onNoteOn(channel, note, velocity, false); 
                }
            )
        );
        extMidiHardwareSerial->setHandleNoteOff(
            fnptr<void(uint8_t channel, uint8_t note, uint8_t velocity)>(
                [this](uint8_t channel, uint8_t note, [[maybe_unused]] uint8_t velocity)
                {
                    this->onNoteOff(channel, note, false);
                }
            )
        );
        extMidiHardwareSerial->setHandleControlChange(
            fnptr<void(uint8_t channel, uint8_t control, uint8_t value)>(
                [this](uint8_t channel, uint8_t control, uint8_t value)
                {
                    this->onControlChange(channel, control, value, false);
                }
            )
        );
        extMidiHardwareSerial->setHandlePitchBend(
            fnptr<void(uint8_t channel, int pitch)>(
                [this](uint8_t channel, int pitch)
                {
                    this->onPitchChange(channel, pitch, false);
                }
            )
        );
        extMidiHardwareSerial->setHandleProgramChange(
            fnptr<void(uint8_t channel, uint8_t program)>(
                [this](uint8_t channel, uint8_t program)
                {
                    this->onProgramChange(channel, program, false);
                }
            )
        );
    }

    /**
     * Light state task, deals with blinking lights.
     */
    void lightStateTask()
    {
        // load
        if (controlStateLightLoadState == LightState::on && !controlStateLightLoadWasOn)
        {
            setControlStateLightLoad(true);
        }
        else if (controlStateLightLoadState == LightState::off && controlStateLightLoadWasOn)
        {
            setControlStateLightLoad(false);
        }
        else if (controlStateLightLoadState == LightState::blinkFast)
        {
            setControlStateLightLoad(!controlStateLightLoadWasOn);
        }
        else if (controlStateLightLoadState == LightState::blinkSlow && lightStateMetroCounter % LIGHT_STATE_BLINK_SLOW_MODULUS == 0)
        {
            setControlStateLightLoad(!controlStateLightLoadWasOn);
        }

        // save
        if (controlStateLightSaveState == LightState::on && !controlStateLightSaveWasOn)
        {
            setControlStateLightSave(true);
        }
        else if (controlStateLightSaveState == LightState::off && controlStateLightSaveWasOn)
        {
            setControlStateLightSave(false);
        }
        else if (controlStateLightSaveState == LightState::blinkFast)
        {
            setControlStateLightSave(!controlStateLightSaveWasOn);
        }
        else if (controlStateLightSaveState == LightState::blinkSlow && lightStateMetroCounter % LIGHT_STATE_BLINK_SLOW_MODULUS == 0)
        {
            setControlStateLightSave(!controlStateLightSaveWasOn);
        }

        lightStateMetroCounter++;
    }

    /**
     * Button repeat task, deals with increment/decrement button repeats.
     */
    void buttonRepeatTask()
    {
        if (niNdButtonPressed)
        {
            if (elapsedMillisSinceLastNiNdButtonPress >= buttonRepeatDelayMillis)
            {
                if (elapsedMillisSinceLastNiNdButtonPress >= buttonRepeatFastDelayMillis)
                {
                    handleControllerNoteOn(lastNiNdNote);
                }
                else if (buttonRepeatMetroCounter % BUTTON_REPEAT_SLOW_MODULUS == 0)
                {
                    handleControllerNoteOn(lastNiNdNote);
                }
            }
        }

        buttonRepeatMetroCounter++;
    }

    /**
     * Perform scheduled tasks.
     */
    void task()
    {
        #ifdef DEBUG_CPU_USAGE
        if (cpuMetro.check() == 1)
        {
            synth.logCpuUsageStats();
        }
        #endif

        // the display is updated using a separate thread
        // if (displayMetro.check() == 1)
        // {
        //     displayService.task();
        // }

        if (lightStateMetro.check() == 1)
        {
            lightStateTask();
        }

        if (niNdButtonRepeatStateMetro.check() == 1)
        {
            buttonRepeatTask();
        }
    }
};

#endif