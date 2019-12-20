//
// Created by adrien on 17/12/19.
//

#ifndef MINECRAFT_LAUNCH_PROXY_STATUSREQUESTPACKET_H
#define MINECRAFT_LAUNCH_PROXY_STATUSREQUESTPACKET_H

#include "Packet.h"
#include <QJsonDocument>

class StatusRequestPacket : public Packet {

public:
    ~StatusRequestPacket() override;

    void fromData(QDataStream *stream) override;

    void handle(QTcpSocket *socket) override;

    void toData(QDataStream *stream) override;

private:
    QJsonDocument* jsonDocument;

};


#endif //MINECRAFT_LAUNCH_PROXY_STATUSREQUESTPACKET_H
