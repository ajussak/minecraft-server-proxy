//
// Created by adrien on 19/12/19.
//

#ifndef MINECRAFT_LAUNCH_PROXY_PINGPACKET_H
#define MINECRAFT_LAUNCH_PROXY_PINGPACKET_H

#include "Packet.h"

class PingPacket : public Packet {
public:
    void fromData(QDataStream *stream) override;

    void handle(QTcpSocket *socket) override;

    void toData(QDataStream *stream) override;

private:
    qint64 payload;
};


#endif //MINECRAFT_LAUNCH_PROXY_PINGPACKET_H
