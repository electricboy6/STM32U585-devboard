#include "pins.h"
#include "drivers/interconnect.h"
#include "drivers/pyro.h"
#include "drivers/logger.h"

void hexPrint(byte num);
void hexPrintln(byte num);

void setup() {
    
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