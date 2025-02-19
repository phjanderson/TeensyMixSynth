#ifndef DisplayService_h
#define DisplayService_h

#include <LiquidCrystal.h>
#include <TeensyThreads.h>

#include <string>
#include "Patch.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
static const int rs = 12;
static const int en = 11;
static const int d4 = 5;
static const int d5 = 4;
static const int d6 = 3;
static const int d7 = 2;
static LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/**
 * Display service
 * Handles communication with the LCD2004a display.
 */
class DisplayService
{
private:
    const static uint8_t DISPLAY_WIDTH = 20;
    const static uint8_t DISPLAY_HEIGHT = 4;

    // current parameter group name
    std::string parameterGroupName;
    // current parameter group name, if true, the display will be updated next task() call
    bool parameterGroupNameChanged{false};

    // current parameter name
    std::string parameterName;
    // current parameter name, if true, the display will be updated next task() call
    bool parameterNameChanged{false};

    // current parameter value
    std::string parameterValue;
    // current parameter value, if true, the display will be updated next task() call
    bool parameterValueChanged{false};

    /**
     * Clip and pad a string to a fixed length (to fit the display).
     * 
     * @param text text
     * @param length length
     * @return std::string clipped and padded string
     */
    std::string clipPadString(std::string text, const uint8_t length) const
    {
        if (text.length() != length)
        {
            text.resize(length, ' ');
        }
        return text;
    }

    /**
     * Display a row of text on the display.
     * 
     * @param row row number (0 to 3)
     * @param text text (will be clipped and padded to the display width)
     */
    void displayRow(const uint8_t row, const std::string &text) const
    {
        lcd.setCursor(0, row);
        lcd.print(clipPadString(text, DISPLAY_WIDTH).c_str());
    }

    /**
     * Display a text fragment on a certain position of the display.
     * 
     * @param col column (0 to 19)
     * @param row row (0 to 3)
     * @param length length
     * @param text text (will be clipped and padded to the length specified)
     */
    void displayAtPosition(const uint8_t col, const uint8_t row, const uint8_t length, const std::string &text) const
    {
        lcd.setCursor(col, row);
        lcd.print(clipPadString(text, length).c_str());
    }

public:
    /**
     * Initialize the LCD display and start the display update thread.
     */
    void initialize()
    {
        // set up the LCD's number of columns and rows:
        lcd.begin(DISPLAY_WIDTH, DISPLAY_HEIGHT);

        // start a separate thread to update the display
        // this improves note timing accuracy
        auto taskThread = threads.addThread(
            fnptr<void()>(
                    [this]()
                    {
                        this->taskRunner();
                    }
            )
        );

        // allocate a small time slice for display updates
        threads.setTimeSlice(taskThread, 1);
        // thread 0 is the main thread that executes all the rest
        threads.setTimeSlice(0, 6);
    }
    
    /**
     * Display an error on the first row.
     * 
     * @param error error
     */
    void displayError(const std::string &error) const
    {
        displayRow(0, error);
    }

    /**
     * Display the current state of the synthesizer.
     * 
     * @param state state label (max 4 characters)
     */
    void displayState(const std::string &state) const
    {
        displayAtPosition(0, 0, 5, state);
    }

    /**
     * Display the current patch number.
     * Both the 1-8 + 1-8 based patch number and the MIDI 1-64 program are displayed.
     * 
     * @param patchNumber patch number (0-63)
     */
    void displayPatchNumber(const uint8_t patchNumber) const
    {
        char buffer [9];
        // add 1 to the patch number for display purposes, MIDI software generally uses 1-128 instead of the actual 0-127 numbers
        snprintf(buffer, 9, "%d ~%d", convertPatchNumberToDigits(patchNumber), patchNumber + 1);
        displayAtPosition(5, 0, 7, std::string(buffer));
    }

    /**
     * Display the current patch name.
     * 
     * @param patch current patch
     */
    void displayPatchName(const Patch &patch) const
    {
        displayAtPosition(12, 0, 8, patch.getName());
    }

    /**
     * Display 12345678 underneath the patch name to help with editing the name.
     */
    void displayPatchNameEditNumbers() const
    {
        displayAtPosition(12, 1, 8, "12345678");
    }

    /**
     * Clear 12345678 underneath the patch name.
     */
    void clearPatchNameEditNumbers() const
    {
        displayAtPosition(12, 1, 8, "");
    }

    /**
     * Clear the param group name, name and value on the display.
     */
    void clearParamNameAndValue() const
    {
        displayRow(1, "");
        displayRow(2, "");
        displayRow(3, "");
    }

    /**
     * Display the param group name, name and value on the display.
     * Please note: display updates are postponed until the next task() call to avoid excessive CPU usage during intensive parameter changes.
     * 
     * @param param param
     * @param value param value
     */
    void displayParamNameAndValue(const Param &param, const uint8_t value)
    {
        parameterGroupName.assign(param.getGroupName());
        parameterGroupNameChanged = true;

        parameterName.assign(param.getName());
        parameterNameChanged = true;

        parameterValue.assign(param.stringValue(value));
        parameterValueChanged = true;
    }

    /**
     * Perform delayed tasks.
     * Updates the display if param group name, name or value are tagged as changed.
     * Called by taskRunner() in the display update thread.
     */
    void task()
    {
        if(parameterGroupNameChanged)
        {
            displayRow(1, parameterGroupName);
            parameterGroupNameChanged = false;
        }
        if(parameterNameChanged)
        {
            displayRow(2, parameterName);
            parameterNameChanged = false;
        }
        if(parameterValueChanged)
        {
            displayRow(3, parameterValue);
            parameterValueChanged = false;
        }
    }

    /**
     * Display update thread task runner.
     */
    void taskRunner()
    {
        while (true) {
            this->task();
            threads.yield();
        }
    }
};

#endif