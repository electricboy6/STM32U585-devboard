#include "pins.h"
#include "drivers/interconnect.h"
#include "drivers/pyro.h"
#include "drivers/logger.h"

void hexPrint(byte num);
void hexPrintln(byte num);

void setup() {
    logger::init();
    logger::initSD();
    lfs_file_t file;
    flash_lfs::open(&file, "test.txt", LFS_O_CREAT | LFS_O_RDWR);
    const char* test = "lfs is working!";
    flash_lfs::write(&file, test, sizeof(test));
    flash_lfs::close(&file);
    flash_lfs::unmount();
}

void loop() {

}

void hexPrint(byte num) {
    Serial.print("0x");
    if (num < 16) {
        Serial.print("0");
    }
    Serial.print(num, HEX);
}
void hexPrintln(byte num) {
    hexPrint(num);
    Serial.print('\n');
}