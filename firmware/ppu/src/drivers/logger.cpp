#include "logger.h"

void logger::init() {
    if(!flash::init()) {
        Serial.println("flash NOT OK");
    } else {
        Serial.println("flash OK\nDevice id: " + flash::getJEDEC_ID());
    }
    flash_lfs::mount(true);
}

void logger::initSD() {
    if(!SD.begin()) {
        Serial.println("sd NOT OK");
    }
    file = SD.open(logger::filename, FILE_WRITE);
    Serial.println("sd OK");
}
void logger::endSD() {
    SD.end();
}

void logger::writeSD(const void* data, size_t size) {
    file.write((const byte*)data, size);
}