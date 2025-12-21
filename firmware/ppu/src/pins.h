#pragma once

#include <Arduino.h>
#include <SPI.h>

namespace pins {
    // vbat sense analog pin
    const byte vbat         = PB1;

    // continuity test result analog pin
    const byte cont_test    = PA1;
    const byte arm          = PA8;
    const byte c1_fire      = PB6;
    const byte c2_fire      = PB7;
    const byte c3_fire      = PB8;
    const byte c4_fire      = PB9;
    const byte c5_fire      = PB10;
    const byte c6_fire      = PB11;

    const byte telem_busy   = PA14;
    const byte telem_rst    = PA15;

    const byte piezo        = PA0;


    // mpu
    inline HardwareSerial interconnectSerial(PA10, PA9);

    // broken out on header
    inline HardwareSerial debugSerial(PA3, PA2);

    // flash spi
    inline SPIClass flash(PB5, PB4, PB3, PB2);

    // sd spi
    inline SPIClass sd(PB15, PB14, PB13, PB12);

    // telemetry spi
    inline SPIClass telem(PA7, PA6, PA5, PB0);

    // init all serials and spis
    void init();
}