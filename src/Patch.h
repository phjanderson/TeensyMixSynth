#ifndef Patch_h
#define Patch_h

#include <stdint.h>
#include <string>
#include <map>

#include "Param.h"

/**
 * A Patch consists of a name and a map of parameter ID / paramters value pairs.
 */
class Patch
{
private:
    std::string DEFAULT_NAME{"Init"};

    /**
     * Patch name, fixed length padded with spaces.
     */
    std::string name;

public:
    /**
     * Patch name length, equal to the number of increment / decrement buttons (MIDImix channels).
     */
    const static uint8_t NAME_LENGTH{8};

    /**
     * Constructor with name.
     * 
     * @param name name
     */
    explicit Patch(const std::string &name) : name(name) {
        this->name.resize(NAME_LENGTH, ' ');
    }

    /**
     * Constructor with default name.
     */
    explicit Patch() : Patch(DEFAULT_NAME) {}

    /**
     * Map of parameter ID / paramters value pairs.
     */
    std::map<uint16_t, uint8_t> paramValueMap;

    /**
     * Delete a parameter value.
     * 
     * @param paramId parameter ID
     */
    void deleteParamValue(uint16_t paramId)
    {
        if (!paramValueMap.count(paramId))
        {
            return;
        }
        paramValueMap.erase(paramId);
    }
    
    /**
     * Get a parameter value.
     * 
     * @param paramId parameter ID
     * @return uint8_t value
     */
    uint8_t getParamValue(uint16_t paramId)
    {
        if (!paramValueMap.count(paramId))
        {
            return 0;
        }
        return paramValueMap.at(paramId);
    }
    
    /**
     * Set a parameter value.
     * 
     * @param paramId parameter ID
     * @param value value
     * @param maxValue max value
     * @return uint8_t stored value
     */
    uint8_t setParamValue(uint16_t paramId, uint8_t value, uint8_t maxValue)
    {
        auto paramValue = value <= maxValue ? value : maxValue;
        paramValueMap[paramId] = paramValue;
        return paramValue;
    }

    /**
     * Increment parameter value.
     * 
     * @param paramId parameter ID
     * @param value increment value (use a negative number to decrement the value)
     * @param maxValue max value
     * @return uint8_t stored value
     */
    uint8_t incrementParamValue(uint16_t paramId, int8_t value, uint8_t maxValue)
    {
        auto incrementedValue = paramValueMap[paramId] + value;
        if (incrementedValue < 0)
        {
            incrementedValue = 0;
        }
        else if (incrementedValue > maxValue)
        {
            incrementedValue = maxValue;
        }
        paramValueMap[paramId] = (uint8_t)incrementedValue;

        return (uint8_t)incrementedValue;
    }

    /**
     * Get the patch name.
     * 
     * @return std::string patch name
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * Set the patch name.
     * 
     * @param newName new name (will be clipped and padded to the name length)
     */
    void setName(const std::string &newName)
    {
        name = newName;
        name.resize(NAME_LENGTH, ' ');
    }

    /**
     * Increment a letter of the patch name.
     * 
     * @param pos letter position (1-8)
     */
    void incrementNameLetter(uint8_t pos)
    {
        char &nameLetter = name.at(pos);
        if (nameLetter < 125)
        {
            nameLetter++;
        }
    }

    /**
     * Decrement a letter of the patch name.
     * 
     * @param pos letter position (1-8)
     */
    void decrementNameLetter(uint8_t pos)
    {
        char &nameLetter = name.at(pos);
        if (nameLetter > 32)
        {
            nameLetter--;
        }
    }

    /**
     * Print the content of this patch, for debugging purposes.
     */
    void debugPrint() const
    {
        Serial.print("Name = '");
        Serial.print(name.c_str());
        Serial.println("'");
        
        for (const auto [paramId, paramValue] : paramValueMap)
        {
            Serial.print(paramId);
            Serial.print(" = ");
            Serial.println(paramValue);
        }
    }

};

#endif