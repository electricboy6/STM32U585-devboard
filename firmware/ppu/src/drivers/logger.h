#pragma once

#include <SD.h>
#include "pins.h"
#include "flash/flash_lfs.h"

namespace logger {
    inline const char* filename = "log.txt";

    inline SDFile file;

    void init();

    void writeSD(const byte* data, size_t size);
    void initSD();
};