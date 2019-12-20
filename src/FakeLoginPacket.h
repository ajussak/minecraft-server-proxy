//
// Created by adrien on 19/12/19.
//

#ifndef MINECRAFT_LAUNCH_PROXY_FAKELOGINPACKET_H
#define MINECRAFT_LAUNCH_PROXY_FAKELOGINPACKET_H

#include "Packet.h"
#include <QJsonDocument>
#include <QtCore/QProcess>

class FakeLoginPacket : public Packet {

public:
    FakeLoginPacket();

    virtual ~FakeLoginPacket();

    void fromData(QDataStream *stream) override;

    void handle(QTcpSocket *socket) override;

    void toData(QDataStream *stream) override;

private:
    QJsonDocument* jsonDocument;
    QProcess* process;
};


#endif //MINECRAFT_LAUNCH_PROXY_FAKELOGINPACKET_H
