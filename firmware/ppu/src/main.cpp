#include "drivers/interconnect.h"
#include "drivers/pyro.h"
#include "drivers/logger.h"

void hexPrint(byte num);
void hexPrintln(byte num);
void hexPrintRaw(byte num);

void setup() {
    pins::init();

    digitalWrite(pins::telem_rst, LOW);
    delay(50);
    digitalWrite(pins::telem_rst, HIGH);
    while(!Serial) {}
    Serial.println("Checking interconnect...");
    interconnect::packet* receivedPacket = interconnect::receivePacket();
    interconnect::sendPacket(receivedPacket);
    Serial.println("Check mpu serial for result.");

    Serial.println("Initializing flash and sd card...");
    logger::init();
    logger::initSD();

    // test littlefs write
    flash_lfs::mount(false);
    lfs_file_t file;
    flash_lfs::open(&file, "test.txt", LFS_O_CREAT | LFS_O_RDWR);
    const char* data = "the flash and sd card are working!";
    flash_lfs::write(&file, data, sizeof(data));
    flash_lfs::close(&file);
    flash_lfs::unmount();

    // test littlefs read
    flash_lfs::mount(false);
    flash_lfs::open(&file, "test.txt", LFS_O_RDONLY);
    char* readData = (char*)malloc(sizeof(data));
    flash_lfs::read(&file, readData, sizeof(data));
    flash_lfs::close(&file);
    flash_lfs::unmount();

    if(data != readData) {
        Serial.println("flash NOT OK");
    }

    // test sd write
    logger::writeSD(readData, sizeof(data));
    logger::endSD();

    Serial.println("Check sd's files to see if sd and flash succeded");

    delay(1000);
    Serial.println("Testing lr2021 connection...");

    // test lr2021 connection
    digitalWrite(pins::telem_cs, LOW);
    // send command (GetVersion)
    pins::telem.transfer(0x01);
    pins::telem.transfer(0x01);
    // receive status
    uint16_t status = pins::telem.transfer(0x00) << 8;
    status |= pins::telem.transfer(0x00);
    // receive firmware version (what we actually care about)
    uint16_t firmwareVersion = pins::telem.transfer(0x00) << 8;
    firmwareVersion |= pins::telem.transfer(0x00);
    if(firmwareVersion == 0x0118) {
        Serial.println("lr2021 OK");
    } else {
        Serial.println("lr2021 NOT OK");
        Serial.print("expected firmware 0x0118, got ");
        hexPrint(firmwareVersion >> 8);
        hexPrintRaw(firmwareVersion);
        Serial.println('!');
    }
    Serial.println("Testing pyros...");
    Serial.println("Type \"arm\" to arm, \"disarm\" to disarm, \"test cn\" to test channel n, and \"fire cn\" to fire channel n");
}

void loop() {
    // get command
    String received = Serial.readStringUntil('\n');
    received.trim();
    if(received == "arm") {
        pyro::arm();
        Serial.println("armed");
    } else if(received == "disarm") {
        pyro::disarm();
        Serial.println("disarmed");
    } else if(received.startsWith("test c")) {
        // get the channel number, ascii to number
        byte channel = (byte)received.charAt(6) - 30;
        if(pyro::contTest(channel)) {
            Serial.println("continuity on pyro channel " + channel);
        } else {
            Serial.println("no continuity on pyro channel " + channel);
        }
    } else if (received.startsWith("fire c")) {
        // get the channel number, ascii to number
        byte channel = (byte)received.charAt(6) - 30;
        pyro::fire(channel);
        Serial.print("fired pyro channel " + channel);
        Serial.print(" while the channels were ");
        if(pyro::armed) {
            Serial.println("armed");
        } else {
            Serial.println("disarmed");
        }
    }
}

void hexPrint(byte num) {
    Serial.print("0x");
    hexPrintRaw(num);
}
void hexPrintRaw(byte num) {
    if (num < 16) {
        Serial.print("0");
    }
    Serial.print(num, HEX);
}
void hexPrintln(byte num) {
    hexPrint(num);
    Serial.print('\n');
}