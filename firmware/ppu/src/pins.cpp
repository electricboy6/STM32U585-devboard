#include "pins.h"

void pins::init() {
    SerialUSB.begin(12000000); // 12 mbaud
    while(!SerialUSB.available()) {}

    interconnectSerial.begin(250000, SERIAL_8E1); // 250 kbaud, even parity
    while(!interconnectSerial.available()) {}

    debugSerial.begin(115200); // 115.2 kbaud, standard

    // mode 0, 16mhz
    telem.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));

    // mode 0, 32mhz - max supported speed (flash goes up to 55mhz)
    flash.beginTransaction(SPISettings(32000000, MSBFIRST, SPI_MODE0));

    //sd.beginTransaction(SPISettings(25000000, MSBFIRST, SPI_MODE0));
    
    // 12 bit analog reads
    analogReadResolution(12);
}