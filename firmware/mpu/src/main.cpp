#include "drivers/interconnect.h"
#include <SparkFun_MMC5983MA_Arduino_Library.h>
#include <SparkFun_BMP581_Arduino_Library.h>
#include <SparkFun_u-blox_GNSS_v3.h>

void hexPrint(byte num);
void hexPrintln(byte num);

byte testPacket[] = {
    0x00,
    0xFF,
    0x88,
    0x44,
    0xAA,
    0x01,
    0xA0,
    0x10
};
byte* receivedPacket;

// scan both i2c busses for devices - each should have 3
// also test for proper echoing on the interconnect
void setup() {
    pins::init();
    // wait for usb connect - DO NOT USE THIS IN FLIGHT FIRMWARE!
    // Serial is SerialUSB with our compilation settings
    while(!Serial) {}

    // it's literally an i2c scanner
    Serial.println("Checking i2c1...");
    byte error;
    byte numDevices = 0;
    for(byte address = 1; address < 127; address++) {
        pins::i2cFast.beginTransmission(address);
        error = pins::i2cFast.endTransmission();
        if(error == 0) {
            Serial.print("I2C device found at address ");
            hexPrintln(address);
            numDevices++;
        } else if(error == 4) {
            Serial.print("Unknown error at address ");
            hexPrintln(address);
        }
    }
    if(numDevices == 0) {
        Serial.println("No devices found on i2c1 - That's a really big problem");
    } else if (numDevices == 3) {
        Serial.println("i2c1 OK - 3 devices found");
    } else {
        Serial.println(numDevices + " found on i2c1 - not what we expected, check the soldering");
    }

    Serial.println("Checking i2c2...");
    numDevices = 0;
    for(byte address = 1; address < 127; address++) {
        pins::i2cSlow.beginTransmission(address);
        error = pins::i2cSlow.endTransmission();
        if(error == 0) {
            Serial.print("I2C device found at address ");
            hexPrintln(address);
            numDevices++;
        } else if(error == 4) {
            Serial.print("Unknown error at address ");
            hexPrintln(address);
        }
    }
    if(numDevices == 0) {
        Serial.println("No devices found on i2c2 - That's a really big problem");
    } else if (numDevices == 3) {
        Serial.println("i2c2 OK - 3 devices found");
    } else {
        Serial.println(numDevices + " found on i2c2 - not what we expected, check the soldering");
    }

    delay(5000);
    Serial.println("Checking interconnect...");

    interconnect::sendPacket((interconnect::packet*)(&testPacket));
    receivedPacket = (byte*)interconnect::receivePacket();

    // check each byte
    bool interconnectGood = true;
    for(int i = 0; i < PACKET_SIZE; i++) {
        if(receivedPacket[i] != testPacket[i]) {
            interconnectGood = false;
        }
    }

    if(interconnectGood) {
        Serial.println("interconnect OK");
    } else {
        Serial.println("interconnect NOT OK");
        Serial.println("Received: [");
        for(int i = 0; i < PACKET_SIZE; i++) {
            hexPrint(receivedPacket[i]);
            Serial.print(", ");
        }
        Serial.println("]\nExpected: ");
        for(int i = 0; i < PACKET_SIZE; i++) {
            hexPrint(testPacket[i]);
            Serial.print(", ");
        }
        Serial.println(']');
    }
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