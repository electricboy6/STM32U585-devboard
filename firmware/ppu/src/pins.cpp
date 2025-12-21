#include "pins.h"

void pins::init() {
    SerialUSB.begin(12000000); // 12 mbaud
    while(!SerialUSB.available()) {}

    interconnectSerial.begin(250000, SERIAL_8E1); // 250 kbaud, even parity
    while(!interconnectSerial.available()) {}

    debugSerial.begin(115200); // 115.2 kbaud, standard

    telem.beginTransaction(SPISettings(16000000, ));
}