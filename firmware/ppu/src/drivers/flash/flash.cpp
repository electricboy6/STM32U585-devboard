#include "flash.h"

void sendAddress(uint32_t address);

bool flash::init() {
    // initialize
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

void flash::sleep() {
    flash::spiCommand(SLEEP);

    flash::deselect();
}
void flash::wakeup() {
    flash::spiCommand(WAKE);

    flash::deselect();
}
void flash::reset() {
    // enable reset
    flash::spiCommand(RESET_ENABLE);
    flash::deselect();

    // actually reset
    flash::spiCommand(RESET_CHIP);
    flash::deselect();
}

byte flash::readByte(uint32_t address) {
    // send command
    flash::spiCommand(READ_ARRAY);
    sendAddress(address);
    // get response
    byte data = pins::flash.transfer(0);

    flash::deselect();
    return data;
}
void flash::readBytes(uint32_t address, void* buf, uint32_t size) {
    // send command
    flash::spiCommand(READ_ARRAY);
    sendAddress(address);
    // since we're using the lower latency command, no dummy byte is needed
    for(uint32_t i = 0; i < size; i++) {
        ((byte*)buf)[i] = pins::flash.transfer(0);
    }

    flash::deselect();
}

void flash::writeByte(uint32_t address, byte data) {
    // send command
    flash::spiCommand(PROGRAM_PAGE, true);
    sendAddress(address);
    // send data
    pins::flash.transfer(data);

    flash::deselect();
}
void flash::writeBytes(uint32_t address, const void* buf, byte size) {
    // send command
    flash::spiCommand(PROGRAM_PAGE, true);
    sendAddress(address);
    // send data
    for(byte i = 0; i < size; i++) {
        pins::flash.transfer(((byte*)buf)[i]);
    }

    flash::deselect();
}

void flash::blockErase4K(uint32_t address) {
    // send command
    flash::spiCommand(BLOCK_ERASE_4K, true);
    sendAddress(address);

    flash::deselect();
}
void flash::blockErase32K(uint32_t address) {
    // send command
    flash::spiCommand(BLOCK_ERASE_32K, true);
    sendAddress(address);

    flash::deselect();
}
void flash::blockErase64K(uint32_t address) {
    // send command
    flash::spiCommand(BLOCK_ERASE_64K, true);
    sendAddress(address);

    flash::deselect();
}
void flash::chipErase() {
    // send command (this one takes a while)
    flash::spiCommand(CHIP_ERASE);

    flash::deselect();
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
    // get upper half of result (idk it wouldn't let me do it with just a uint64_t so this is what I'm doing instead)
    uint32_t uuid_high = pins::flash.transfer(0) << 24;
    uuid_high |= pins::flash.transfer(0) << 16;
    uuid_high |= pins::flash.transfer(0) << 8;
    uuid_high |= pins::flash.transfer(0);
    // get lower half of result
    uint32_t uuid_low = pins::flash.transfer(0) << 24;
    uuid_low |= pins::flash.transfer(0) << 16;
    uuid_low |= pins::flash.transfer(0) << 8;
    uuid_low |= pins::flash.transfer(0);

    flash::deselect();
    return (((uint64_t)uuid_high) << 32) | ((uint64_t)uuid_low);
}

inline bool flash::isBusy() {
    // get bit 0 of the status register
    return flash::readStatus() & 1;
}
inline void flash::spiCommand(byte command, bool isWrite) {
    // make sure write protect is off when we do a write command
    if(isWrite) {
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
// DRY sucks but in this case it's valid
inline void sendAddress(uint32_t address) {
    pins::flash.transfer(address >> 16);
    pins::flash.transfer(address >> 8);
    pins::flash.transfer(address);
}