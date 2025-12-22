#pragma once

#include <SPI.h>
#include "pins.h"

// command defs
const byte WRITE_ENABLE     = 0x06;
const byte WRITE_DISABLE    = 0x04;

const byte PROGRAM_PAGE     = 0x02; // 1-256 bytes
const byte BLOCK_ERASE_4K   = 0x20;
const byte BLOCK_ERASE_32K  = 0x52;
const byte BLOCK_ERASE_64K  = 0xD8;
const byte CHIP_ERASE       = 0x60; // 0xC7 is an alias

const byte READ_STATUS      = 0x05;
const byte WRITE_STATUS     = 0x01;

const byte READ_ARRAY       = 0x03; // limits the chip to 55mhz but the st is lower - gets rid of the 1 byte overhead

const byte SLEEP            = 0xB9;
const byte WAKE             = 0xAB;

const byte READ_JEDEC_ID    = 0x9F;
const byte READ_UUID        = 0x4B;

const byte RESET_ENABLE     = 0x66;
const byte RESET_CHIP       = 0x99;

const uint32_t EXPECTED_JEDEC_ID = 0x001F8401; // pg 43 on the datasheet

namespace flash {
    bool init();

    byte readStatus();
    bool isBusy();

    uint32_t getJEDEC_ID();
    uint64_t getDeviceID();

    byte readByte(uint32_t address);
    void readBytes(uint32_t address, void* buf, uint32_t size);

    void writeByte(uint32_t address, byte data);
    void writeBytes(uint32_t address, const void* buf, uint16_t size);

    void chipErase();
    void blockErase4K(uint32_t address);
    void blockErase32K(uint32_t address);
    void blockErase64K(uint32_t address);

    void sleep();
    void wakeup();
    void close();

    void spiCommand(byte command, bool isWrite=false);
    void select();
    void deselect();
}