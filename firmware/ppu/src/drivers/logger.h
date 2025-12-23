#pragma once

#include <SD.h>
#include "pins.h"
#include "flash/flash_lfs.h"

namespace logger {
    inline const char* filename = "test.txt";

    inline SDFile file;

    void init();

    void writeSD(const void* data, size_t size);
    void initSD();
    void endSD();
};