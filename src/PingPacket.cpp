//
// Created by adrien on 19/12/19.
//

#include "PingPacket.h"

void PingPacket::fromData(QDataStream *stream) {
    *stream >> payload;
}

void PingPacket::handle(QTcpSocket *socket) {

}

void PingPacket::toData(QDataStream *stream) {
    Packet::writeVarInt(0x01, stream);
    *stream << payload;
}
