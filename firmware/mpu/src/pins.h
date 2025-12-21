#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace pins {
    const int mag_int = PA0;
    const int bmp_int = PA1;
    const int gps_rst = PA4;
    const int gps_int = PA5;
    const int imu1_int = PB3;
    const int imu2_int = PB5;
    const int accel_int = PB15;

    // +X
    const int servo1 = PA6;
    // +Y
    const int servo2 = PA7;
    // -X
    const int servo3 = PB0;
    // -Y
    const int servo4 = PB1;

    // ppu
    inline HardwareSerial interconnectSerial(PA10, PA9);

    // broken out on header
    inline HardwareSerial debugSerial(PA3, PA2);

    // imus, baro
    inline TwoWire i2cFast(PB7, PB6);

    // mag, gps, accel
    inline TwoWire i2cSlow(PB14, PB13);

    // init all serials and i2cs
    void init();
}