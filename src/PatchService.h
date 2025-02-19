#ifndef PatchService_h
#define PatchService_h

#include <stdint.h>
#include <string>
#include <map>

#include "Param.h"

#include <SD.h>
#include <LittleFS.h>

static LittleFS_Program littleFS;

// Specify size to use of onboard Teensy Program Flash chip
// This creates a LittleFS drive in Teensy PCB Flash. 
static const uint32_t PROG_FLASH_SIZE{1024 * 1024 * 1};

/**
 * The PatchService handles loading and saving patches to SD or [LittleFS](https://github.com/PaulStoffregen/LittleFS).
 */
class PatchService
{
private:
    /**
     * Reference to the parameter map, used for determining available parameters and initial values.
     */
    const std::map<uint16_t, const Param *> *paramMap;

    DisplayService * displayService;

    bool sdInitialized{false};

    /**
     * Convert a patch number (0-63) to a patch file name.
     * 
     * @param patchNumber patch number
     * @return std::string file name
     */
    std::string patchNumberToFileName(uint8_t patchNumber)
    {
        std::string fileName;
        fileName.append("tmixpatch/");
        fileName.append(std::to_string(patchNumber));
        fileName.append(".tmixpatch");

        return fileName;
    }

    /**
     * Get a parameter value map initialized with default values.
     * 
     * @return std::map<uint16_t, uint8_t> parameter map
     */
    std::map<uint16_t, uint8_t> getPatchInitParamValueMap() const
    {
        std::map<uint16_t, uint8_t> paramValueMap;
        for (const auto [paramId, param] : *paramMap)
        {
            paramValueMap[paramId] = param->getInitialValue();
        }
        return paramValueMap;
    }

    /**
     * Load a patch.
     * 
     * @param patchNumber patch number
     * @param fs FS
     * @return Patch patch
     */
    Patch loadPatch(const uint8_t patchNumber, FS &fs)
    {
        Patch patch = initPatch();

        char patchNameBuffer[Patch::NAME_LENGTH]{" "};
        uint16_t paramId;
        uint8_t paramValue;

        // try opening the file
        File file = fs.open(patchNumberToFileName(patchNumber).c_str());
        if (file)
        {
            Serial.print("File size: ");
            Serial.println(file.available());

            // verify if the signature is correct
            char signatureBuffer[] = "    ";
            file.read(&signatureBuffer, FILE_SIGNATURE_SIZE);

            if (strcmp(signatureBuffer, FILE_SIGNATURE))
            {
                Serial.println("Error loading patch, invalid signature");
                Serial.println("File signature:");
                Serial.println(signatureBuffer);
                Serial.println("Expected signature:");
                Serial.println(FILE_SIGNATURE);
            }
            else
            {
                // load the patch name
                if (file.available() >= Patch::NAME_LENGTH)
                {
                    file.read(&patchNameBuffer, Patch::NAME_LENGTH);
                    patch.setName(std::string(patchNameBuffer));

                    // load the parameter values
                    while (file.available() >= 3)
                    {
                        file.read(&paramId, 2);
                        file.read(&paramValue, 1);

                        patch.paramValueMap[paramId] = paramValue;
                    }
                }
                else
                {
                    Serial.println("Error reading patch name");
                }
            }

            file.close();
        }
        else
        {
            Serial.println("Error opening patch file");
        }

        return patch;
    }

    /**
     * Save a patch.
     * 
     * @param patchNumber patch number
     * @param patch patch
     * @param fs FS
     */
    void savePatch(const uint8_t patchNumber, const Patch &patch, FS &fs)
    {
        Serial.println("Saving patch to file");

        std::string fileName = patchNumberToFileName(patchNumber);

        fs.remove(fileName.c_str());

        File file = fs.open(fileName.c_str(), FILE_WRITE);
        if (file)
        {
            // write the signature
            file.write(FILE_SIGNATURE, FILE_SIGNATURE_SIZE);

            // write the patch name
            file.write(patch.getName().c_str(), Patch::NAME_LENGTH);

            // write the parameter ID / value pairs
            for (const auto [paramId, paramValue] : patch.paramValueMap)
            {
                file.write(&paramId, 2);
                file.write(&paramValue, 1);
            }

            file.close();
        }
        else
        {
            Serial.println("Error opening patch file");
        }
    }

public:
    /**
     * Initialize the patch service.
     * 
     * @param paramMap reference to the parameter map
     */
    void initialize(const std::map<uint16_t, const Param *> *paramMap, DisplayService * displayService)
    {
        this->paramMap = paramMap;
        this->displayService = displayService;

        Serial.println("Initializing LittleFS ...");

        // checks that the LittFS program has started with the disk size specified
        if (!littleFS.begin(PROG_FLASH_SIZE))
        {
            Serial.println("Error starting PROGRAM FLASH DISK");
            displayService->displayError("Fail PROG FLASH DISK");
            while (true)
            {
                // Error, so don't do anything more - stay stuck here
            }
        }
        Serial.println("LittleFS initialized.");


        Serial.println("Initializing SD ...");

        // check that the SD card is available
        if (!SD.begin(BUILTIN_SDCARD)) {
            Serial.println("Failed to initialize SD");
            //TODO: add compile setting to choose between SD and LittleFS?
            displayService->displayError("Failed to init SD");
            // delay(5000);
            while (true);
        }
        else
        {
            sdInitialized = true;
            Serial.println("SD initialized.");

            // check if the tmixpatch folder exists
            if (!SD.exists("tmixpatch"))
            {
                // create the tmixpatch folder
                if (!SD.mkdir("tmixpatch"))
                {
                    Serial.println("Failed to create folder tmixpatch on SD");
                    sdInitialized = false;

                    displayService->displayError("Fail tmixpatch on SD");
                    // delay(5000);
                    while (true);
                }
                else
                {
                    Serial.println("Created folder tmixpatch on SD");
                }
            }
            else
            {
                Serial.println("Folder tmixpatch already exists on SD");
            }
        }
    }

    /**
     * Generate a patch using the initial values of all parameters.
     * 
     * @return Patch patch
     */
    Patch initPatch()
    {
        Patch patch;
        patch.paramValueMap = getPatchInitParamValueMap();
        return patch;
    }

    /**
     * Load a patch.
     * 
     * @param patchNumber patch number
     * @return Patch patch
     */
    Patch loadPatch(const uint8_t patchNumber)
    {
        return loadPatch(patchNumber, SD);
    }

    /**
     * Save a patch.
     * 
     * @param patchNumber patch number
     * @param patch patch
     */
    void savePatch(const uint8_t patchNumber, const Patch &patch)
    {
        savePatch(patchNumber, patch, SD);
    }

    /**
     * Delete all patches.
     */
    void deleteAllPatches()
    {
        Serial.println("Deleting all patch files");

        Serial.println("TODO: disabled for now");
        // for (uint8_t patchNumber = 0 ; patchNumber <= 63 ; patchNumber++)
        // {
        //     littleFS.remove(patchNumberToFileName(patchNumber).c_str());
        // }
    }

    /**
     * Copy all patches from LittleFS to SD.
     */
    void copyAllPatchesToSd()
    {
        Serial.println("Copying all patch files to SD");

        for (uint8_t patchNumber = 0 ; patchNumber <= 63 ; patchNumber++)
        {
            Patch patch = loadPatch(patchNumber, littleFS);
            savePatch(patchNumber, patch, SD);
        }
    }

};

#endif