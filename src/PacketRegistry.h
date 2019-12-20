//
// Created by adrien on 17/12/19.
//

#ifndef MINECRAFT_LAUNCH_PROXY_PACKETREGISTRY_H
#define MINECRAFT_LAUNCH_PROXY_PACKETREGISTRY_H

#include "Packet.h"

class PacketRegistry {

public:
    static PacketRegistry& getInstance()
    {
        static PacketRegistry    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    ~PacketRegistry();
    std::map<int, Packet*>* getRegistry(int state);
    void registerPacket(int state, int packetId, Packet* packet);
private:
    PacketRegistry() {};
    std::map<int, Packet*> statePackets;
    std::map<int, Packet*> loginPackets;
};


#endif //MINECRAFT_LAUNCH_PROXY_PACKETREGISTRY_H
