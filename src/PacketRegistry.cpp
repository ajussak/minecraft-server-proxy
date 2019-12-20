//
// Created by adrien on 17/12/19.
//

#include "PacketRegistry.h"

PacketRegistry::~PacketRegistry() {
    for (auto &m : statePackets) {
        delete m.second;
    }

    for (auto &m : loginPackets) {
        delete m.second;
    }
}

std::map<int, Packet *> *PacketRegistry::getRegistry(int state) {
    if (state == 1)
        return &statePackets;
    else if (state == 2)
        return &loginPackets;

    return nullptr;
}

void PacketRegistry::registerPacket(int state, int packetId, Packet *packet) {
    if (state == 1)
        statePackets.insert(std::pair<int, Packet *>(packetId, packet));
    else if (state == 2)
        loginPackets.insert(std::pair<int, Packet *>(packetId, packet));
}
