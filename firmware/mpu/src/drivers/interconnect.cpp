#include "interconnect.h"
#include "assert.h"

namespace interconnect {
    void sendPacket(const packet* data) {
        // reinterpret casts scare me
        size_t bytes_sent = pins::interconnectSerial.write((const byte*)data, PACKET_SIZE);

        // make sure the packet is actually sent
        pins::interconnectSerial.flush();

        // probably do real error handling in the future
        assert(bytes_sent == PACKET_SIZE);
    }
    void sendPacket(const byte data[PACKET_SIZE + 1]) {
        sendPacket((const packet*) data);
    }

    void receivePacket(packet* buf) {
        // wait until we have a packet to receive
        while(!pins::interconnectSerial.available() >= PACKET_SIZE) {}
        // read from serial
        size_t bytesRead = pins::interconnectSerial.readBytes((byte*)buf, PACKET_SIZE);

        // check result - probably move to error handling in the future
        assert(bytesRead == PACKET_SIZE);
    }
    void receivePacket(byte buf[PACKET_SIZE + 1]) {
        receivePacket((packet*) buf);
    }

    packet* receivePacket() {
        // make the right sized buffer
        packet* buf = (packet*)malloc(PACKET_SIZE);

        receivePacket(buf);

        return buf;
    }
}
