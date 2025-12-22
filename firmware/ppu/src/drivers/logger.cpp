#include "logger.h"

void logger::init() {
    if(!flash::init()) {
        Serial.println("Flash init failed! (MAKE SURE FOR FLIGHT FIRMWARE TO DISABLE STATE INCREASE!)");
    } else {
        Serial.println("Flash OK\nDevice id: " + flash::getJEDEC_ID());
    }
}

void logger::initSD() {
    if(!SD.begin()) {
        Serial.println("SD library init failed! Continuing with flash only.");
    }
    file = SD.open(logger::filename, FILE_WRITE);
}

void logger::writeSD(const byte* data, size_t size) {
    file.write(data, size);
}
