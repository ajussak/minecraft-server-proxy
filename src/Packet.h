//
// Created by adrien on 17/12/19.
//

#ifndef MINECRAFT_LAUNCH_PROXY_PACKET_H
#define MINECRAFT_LAUNCH_PROXY_PACKET_H

#include <QtCore/QDataStream>
#include <QtNetwork/QTcpSocket>

class Packet {

public:
    virtual ~Packet() {};
    static qint32 readVarInt(QDataStream* stream);
    static qint64 readVarLong(QDataStream* stream);
    static qint32 writeVarInt(qint32 i, QDataStream* stream);
    static qint32 writeVarLong(qint64 i, QDataStream* stream);
    static void writeString(QString s, QDataStream* stream);
    static QString readString(QDataStream* stream);
    virtual void fromData(QDataStream* stream) = 0;
    virtual void handle(QTcpSocket* socket) = 0;
    virtual void toData(QDataStream* stream) = 0;
};


#endif //MINECRAFT_LAUNCH_PROXY_PACKET_H
