#pragma once

#include "pins.h"

namespace pyro {
    static bool armed = false;
    const byte firePins[] = {
        pins::c0_fire,
        pins::c1_fire,
        pins::c2_fire,
        pins::c3_fire,
        pins::c4_fire,
        pins::c5_fire,
    };

    void init();

    // forcibly disarms
    byte contTest();
    // forcibly disarms
    bool contTest(byte channel);

    void arm();
    void disarm();

    void fire(byte channel);
    void stopFire(byte channel);
}