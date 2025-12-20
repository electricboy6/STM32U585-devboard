#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace pins {
    // ppu
    inline HardwareSerial interconnectSerial(PA_10, PA_9);

    // broken out on header
    inline HardwareSerial debugSerial(PA_3, PA_2);

    // imus, baro
    inline TwoWire i2cFast(PB_7, PB_6);

    // mag, gps, accel
    inline TwoWire i2cSlow(PB_14, PB_13);

    // init all serials and i2cs
    void init();
}