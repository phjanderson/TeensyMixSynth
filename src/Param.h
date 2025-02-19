#ifndef Param_h
#define Param_h

#include <Arduino.h>
#include <stdint.h>
#include <array>
#include <string>
#include <functional>

#include "MiscUtil.h"
#include "Constants.h"
#include "Synth.h"

/**
 * A Param represents a parameter of the synthesizer affecting either the sound or the behaviour.
 */
class Param
{
private:
    /**
     * Default string value function, converting 0.0f - 1.0f to 0% to 100%.
     * 
     * @param param param
     * @param value value
     * @return std::string value sting
     */
    static std::string defaultStringValueFunc([[maybe_unused]] const Param *param, const uint8_t value)
    {
        return formatString("%d%%", 100 * value / 127);
    };
    /**
     * Parameter ID, also used for storing params in patches.
     */
    uint16_t paramId;
    /**
     * Menu item ID (0-63).
     * A value of 255 means "disabled".
     */
    uint8_t menuId{255};
    /**
     * Name of the parameter group.
     */
    std::string groupName;
    /**
     * Name of the parameter.
     */
    std::string name;
    /**
     * Control change used for sending and receiving parameter changes from the external MIDI.
     * A value of 255 means "disabled".
     */
    uint8_t midiCc{255};
    /**
     * Control change used for receiving parameter changes from the MIDImix controller.
     * A value of 255 means "disabled".
     */
    uint8_t controllerCc{255};
    /**
     * Notes used for sending / receiving increment button presses from the MIDImix controller.
     * A value of 255 means "disabled".
     */
    uint8_t controllerNi{255};
    /**
     * Notes used for sending / receiving decrement button presses from the MIDImix controller.
     * A value of 255 means "disabled".
     */
    uint8_t controllerNd{255};
    /**
     * Intial value, between 0 and maxValue.
     */
    uint8_t initialValue;
    /**
     * Max value, up to 127.
     */
    uint8_t maxValue;
    /**
     * Function reference to a (lambda) function to be called to update the synthesizer (whenever the parameter value changes).
     */
    std::function<void(const Param *, Synth &, const uint8_t)> updateSynthFunc;
    /**
     * Function reference to a (lambda) function to convert a parameter value to a text to be displayed on the display.
     */
    std::function<std::string(const Param *, const uint8_t)> stringValueFunc = &defaultStringValueFunc;

public:
    /**
     * Constructor for menu params.
     */
    Param(
        const uint16_t paramId,
        const uint8_t menuId,
        const std::string &groupName,
        const std::string &name,
        const uint8_t midiCc,
        const uint8_t initialValue,
        const uint8_t maxValue,
        std::function<void(const Param *, Synth &, const uint8_t)> const &updateSynthFunc) : paramId(paramId), menuId(menuId), groupName(groupName), name(name), midiCc(midiCc), initialValue(initialValue), maxValue(maxValue), updateSynthFunc(updateSynthFunc){};

    /**
     * Constructor for menu params.
     */
    Param(
        const uint16_t paramId,
        const uint8_t menuId,
        const std::string &groupName,
        const std::string &name,
        const uint8_t midiCc,
        const uint8_t initialValue,
        const uint8_t maxValue,
        std::function<void(const Param *, Synth &, const uint8_t)> const &updateSynthFunc,
        std::function<std::string(const Param *, const uint8_t)> const &stringValueFunc) : paramId(paramId), menuId(menuId), groupName(groupName), name(name), midiCc(midiCc), initialValue(initialValue), maxValue(maxValue), updateSynthFunc(updateSynthFunc){};

    /**
     * Constructor for control params.
     */
    Param(
        const uint16_t paramId,
        const std::string &groupName,
        const std::string &name,
        const uint8_t midiCc,
        const uint8_t controllerCc,
        const uint8_t initialValue,
        const uint8_t maxValue,
        std::function<void(const Param *, Synth &, const uint8_t)> const &updateSynthFunc) : paramId(paramId), groupName(groupName), name(name), midiCc(midiCc), controllerCc(controllerCc), initialValue(initialValue), maxValue(maxValue), updateSynthFunc(updateSynthFunc){};

    /**
     * Constructor for control params.
     */
    Param(
        const uint16_t paramId,
        const std::string &groupName,
        const std::string &name,
        const uint8_t midiCc,
        const uint8_t controllerCc,
        const uint8_t initialValue,
        const uint8_t maxValue,
        std::function<void(const Param *, Synth &, const uint8_t)> const &updateSynthFunc,
        std::function<std::string(const Param *, const uint8_t)> const &stringValueFunc) : paramId(paramId), groupName(groupName), name(name), midiCc(midiCc), controllerCc(controllerCc), initialValue(initialValue), maxValue(maxValue), updateSynthFunc(updateSynthFunc), stringValueFunc(stringValueFunc){};

    /**
     * Constructor for control params.
     */
    Param(
        const uint16_t paramId,
        const std::string &groupName,
        const std::string &name,
        const uint8_t midiCc,
        const uint8_t controllerNi,
        const uint8_t controllerNd,
        const uint8_t initialValue,
        const uint8_t maxValue,
        std::function<void(const Param *, Synth &, const uint8_t)> const &updateSynthFunc) : paramId(paramId), groupName(groupName), name(name), midiCc(midiCc), controllerNi(controllerNi), controllerNd(controllerNd), initialValue(initialValue), maxValue(maxValue), updateSynthFunc(updateSynthFunc){};

    /**
     * Constructor for control params.
     */
    Param(
        const uint16_t paramId,
        const std::string &groupName,
        const std::string &name,
        const uint8_t midiCc,
        const uint8_t controllerNi,
        const uint8_t controllerNd,
        const uint8_t initialValue,
        const uint8_t maxValue,
        std::function<void(const Param *, Synth &, const uint8_t)> const &updateSynthFunc,
        std::function<std::string(const Param *, const uint8_t)> const &stringValueFunc) : paramId(paramId), groupName(groupName), name(name), midiCc(midiCc), controllerNi(controllerNi), controllerNd(controllerNd), initialValue(initialValue), maxValue(maxValue), updateSynthFunc(updateSynthFunc), stringValueFunc(stringValueFunc){};


    /**
     * Update this param in the synth using the given value.
     * 
     * @param synth synth
     * @param value value
     */
    void updateSynth(Synth &synth, uint8_t value) const
    {
        this->updateSynthFunc(this, synth, value);
    }

    /**
     * Format the string value for this param using the given value.
     * 
     * @param value value
     * @return std::string string value
     */
    std::string stringValue(uint8_t value) const
    {
        return this->stringValueFunc(this, value);
    }

    /**
     * Get the parameter ID.
     * 
     * @return uint16_t parameter ID
     */
    uint16_t getParamId() const
    {
        return paramId;
    }

    /**
     * Get the parameter group name.
     * 
     * @return std::string parameter group name
     */
    std::string getGroupName() const
    {
        return groupName;
    }

    /**
     * Get the parameter name.
     * 
     * @return std::string parameter name
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * Get the external MIDI control change.
     * 
     * @return uint8_t control change
     */
    uint8_t getMidiCc() const
    {
        return midiCc;
    }

    /**
     * Get the controller MIDI control change.
     * 
     * @return uint8_t control change
     */
    uint8_t getControllerCc() const
    {
        return controllerCc;
    }

    /**
     * Get the controller note increment.
     * 
     * @return uint8_t note
     */
    uint8_t getControllerNi() const
    {
        return controllerNi;
    }

    /**
     * Get the controller note decrement.
     * 
     * @return uint8_t note
     */
    uint8_t getControllerNd() const
    {
        return controllerNd;
    }

    /**
     * Get the initial value.
     * 
     * @return uint8_t initial value
     */
    uint8_t getInitialValue() const
    {
        return initialValue;
    }

    /**
     * Get the max value.
     * 
     * @return uint8_t max value
     */
    uint8_t getMaxValue() const
    {
        return maxValue;
    }

    /**
     * Get the menu ID.
     * 
     * @return uint8_t menu ID
     */
    uint8_t getMenuId() const
    {
        return menuId;
    }
};

#endif