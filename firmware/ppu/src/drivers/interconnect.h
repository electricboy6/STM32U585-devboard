#pragma once

#include "pins.h"

#define PACKET_SIZE 8

/*
PACKET STRUCTURE
1 byte header, everything else data
header is just packet type - up to 256 packet types
for this test, we're just using id 0
*/

namespace interconnect {
    struct packet {
        byte id;
        byte data[PACKET_SIZE];
    };

    void sendPacket(const packet* data);
    void sendPacket(const byte data[PACKET_SIZE + 1]);
    packet* receivePacket();
    void receivePacket(interconnect::packet* buf);
    void receivePacket(byte buf[PACKET_SIZE + 1]);
}
