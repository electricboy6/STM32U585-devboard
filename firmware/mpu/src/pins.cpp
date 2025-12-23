#include "pins.h"

void pins::init() {
    SerialUSB.begin(1000000); // 1 mbaud
    while(!SerialUSB.available()) {}

    interconnectSerial.begin(250000, SERIAL_8E1); // 250 kbaud, even parity
    while(!interconnectSerial.available()) {}

    debugSerial.begin(115200); // 115.2 kbaud, standard

    i2cFast.begin();
    i2cFast.setClock(1000000); // fast mode plus, 1mhz

    i2cSlow.begin();
    i2cSlow.setClock(400000); // fast mode, 400khz
}