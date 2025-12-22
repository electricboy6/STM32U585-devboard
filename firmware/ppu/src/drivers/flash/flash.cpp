#include "flash.h"

bool flash::init() {
    // initialize
    pinMode(pins::flash_cs, OUTPUT);
    flash::deselect();

    // make sure the chip isn't in a bad state
    flash::wakeup();

    if(flash::getJEDEC_ID() == EXPECTED_JEDEC_ID) {
        // chip responded with the correct JEDEC id, sanity check passed
        flash::spiCommand(WRITE_STATUS, true);
        // turn off all write protection
        pins::flash.transfer(0x00);
        return true;
    }
    // uh oh, sanity check failed
    return false;
}

byte flash::readStatus() {
    flash::select();
    // send command
    pins::flash.transfer(READ_STATUS);
    // get response
    byte status = pins::flash.transfer(0x00);
    flash::deselect();
    return status;
}

uint32_t flash::getJEDEC_ID() {
    // send command
    flash::spiCommand(READ_JEDEC_ID);
    // get result
    uint32_t id = pins::flash.transfer(0) << 16;
    id |= pins::flash.transfer(0) << 8;
    id |= pins::flash.transfer(0);

    flash::deselect();
    return id;
}

uint64_t flash::getDeviceID() {
    // send command
    flash::spiCommand(READ_UUID);
    // 4 dummy bytes
    pins::flash.transfer(0);
    pins::flash.transfer(0);
    pins::flash.transfer(0);
    pins::flash.transfer(0);
    // get result (idk why it says this overflows, will need to look into it later)
    uint64_t uuid = pins::flash.transfer(0) << 56;
    uuid |= pins::flash.transfer(0) << 48;
    uuid |= pins::flash.transfer(0) << 40;
    uuid |= pins::flash.transfer(0) << 32;
    uuid |= pins::flash.transfer(0) << 24;
    uuid |= pins::flash.transfer(0) << 16;
    uuid |= pins::flash.transfer(0) << 8;
    uuid |= pins::flash.transfer(0);

    flash::deselect();
    return uuid;
}

inline bool flash::isBusy() {
    // get bit 0 of the status register
    return flash::readStatus() & 1;
}
inline void flash::spiCommand(byte command, bool isWrite) {
    // make sure write protect is off when we do a write command
    if(isWrite) {
        // todo: figure out if we can optimize this out
        flash::spiCommand(WRITE_ENABLE);
        flash::deselect();
    }

    // spinlock until the flash isn't busy
    if(command != WAKE) {
        while(flash::isBusy()) {}
    }
    // actually send the freaking command
    select();
    pins::flash.transfer(command);
}
inline void flash::select() {
    digitalWrite(pins::flash_cs, LOW);
}
inline void flash::deselect() {
    digitalWrite(pins::flash_cs, HIGH);
}