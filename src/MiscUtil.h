#ifndef MiscUtil_h
#define MiscUtil_h

#include <Arduino.h>
#include <stdint.h>
#include <stdarg.h>
#include <vector>
#include <string>

// Miscellaneous functions

// suffix to add when the value is 0.0f
static const std::string ZERO_SUFFIX{" [0]"};
// suffix to add when the value isn't 0.0f
static const std::string NOT_ZERO_SUFFIX{""};

/**
 * Format a string using vsnprintf.
 * A fixed 256 character buffer is used internally.
 * 
 * @param format format
 * @param ... variable arguments list
 * @return std::string formatted string
 */
std::string formatString(const char *format, ...)
{
    va_list args;
    static char buffer[256];
    va_start(args, format);
    vsnprintf(buffer, 256, format, args);
    return std::string(buffer);
}

/**
 * Create a zero suffix (if value is 0.0f).
 * 
 * @param value value
 * @return std::string zero sufix (if value is 0.0f)
 */
std::string zeroSuffix(const float value)
{
    if (value == 0.0f)
    {
        return ZERO_SUFFIX;
    }

    return NOT_ZERO_SUFFIX;
}

/**
 * Convert patch digits (1-8 + 1-8) to a patch number (0-63) as used in MIDI program changes.
 * 
 * @param patchDigit1 patch digit 1 (1-8)
 * @param patchDigit2 patch digit 2 (1-8)
 * @return uint8_t patch number (0-63)
 */
uint8_t convertPatchDigitsToNumber(const uint8_t patchDigit1, const uint8_t patchDigit2)
{
    return (patchDigit1 - 1) * 8 + patchDigit2 -1;
}

/**
 * Convert a patch number (0-63) as used in MIDI program changes to patch digits (1-8 + 1-8).
 * 
 * @param patchNumber patch number (0-63)
 * @return uint8_t patch digits (1-8 + 1-8)
 */
uint8_t convertPatchNumberToDigits(const uint8_t patchNumber)
{
    // first, convert the number from decimal to octal
    uint8_t decimal = patchNumber;
    uint8_t octal = 0;
    uint8_t remainder;
    uint8_t product = 1;
    while (decimal != 0)
    {
        remainder = decimal % 8;
        decimal = decimal / 8;
        octal = octal + (remainder * product);
        product *= 10;
    }
    
    // then add 1 to both digits
    return octal + 11;
}

#endif