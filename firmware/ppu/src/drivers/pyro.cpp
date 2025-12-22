#include "pyro.h"

const uint32_t GOOD_THRESHOLD = (uint32_t)((0.1 * ANALOG_STEPS) / ANALOG_REF); // volts for closed circuit, theoretical 0v (0.65v open circuit)

void pyro::init() {
    pinMode(pins::arm, OUTPUT);
    for(byte i = 0; i < sizeof(pyro::firePins) / sizeof(byte); i++) {
        pinMode(pyro::firePins[i], OUTPUT);
    }

    pyro::disarm();

    pinMode(pins::cont_test, INPUT_ANALOG);
}

bool pyro::contTest(byte channel) {
    pyro::disarm();

    pyro::fire(channel);
    delay(10);
    return analogRead(pins::cont_test) < GOOD_THRESHOLD;
}

byte pyro::contTest() {
    byte result = 0;
    for(byte i = 0; i < sizeof(pyro::firePins) / sizeof(byte); i++) {
        result <<= 1;
        result += pyro::contTest(i);
    }
    return result;
}

void pyro::arm() {
    digitalWrite(pins::arm, HIGH);
}
void pyro::disarm() {
    digitalWrite(pins::arm, LOW);
    for(byte i = 0; i < sizeof(pyro::firePins) / sizeof(byte); i++) {
        pyro::stopFire(i);
    }
}

void pyro::fire(byte channel) {
    digitalWrite(pyro::firePins[channel], HIGH);
}
void pyro::stopFire(byte channel) {
    digitalWrite(pyro::firePins[channel], LOW);
}