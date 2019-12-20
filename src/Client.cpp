//
// Created by adrien on 17/12/19.
//

#include "Client.h"
#include "PacketRegistry.h"

void Client::readClient() {
    QDataStream socketStream(socket);

    forever {
        if (socket->bytesAvailable() <= 0)
            break;

        qint32 size = Packet::readVarInt(&socketStream); //Packet size

        QByteArray packetData = socket->read(size);
        QDataStream packetDataStream(packetData);

        qint32 socketId = Packet::readVarInt(&packetDataStream);

        if (currentPackets != nullptr) {
            if (currentPackets->count(socketId)) {
                Packet *packet = currentPackets->at(socketId);
                packet->fromData(&packetDataStream);
                packet->handle(socket);

                QByteArray byteArrayOutput;
                QDataStream output(&byteArrayOutput, QIODevice::ReadWrite);

                packet->toData(&output);
                if (byteArrayOutput.size() > 0) {

                    QByteArray sizeData;
                    QDataStream sizeOutput(&sizeData, QIODevice::ReadWrite);

                    Packet::writeVarInt(byteArrayOutput.size(), &sizeOutput);

                    socket->write(sizeData);
                    socket->write(byteArrayOutput);
                    socket->flush();
                } else {
                    socket->disconnect();
                    break;
                }
            }
        } else if (socketId == 0x00) { //Handshake
            Packet::readVarInt(&packetDataStream); //Protocol
            Packet::readString(&packetDataStream); //Host

            qint16 port;
            packetDataStream >> port;

            int state = Packet::readVarInt(&packetDataStream);

            currentPackets = PacketRegistry::getInstance().getRegistry(state);
        }
    }
}

Client::Client(QObject *parent, QTcpSocket *socket) : QObject(parent), socket(socket) {
    connect(socket, SIGNAL(readyRead()),this, SLOT(readClient()));
    //connect(socket, SIGNAL(connected()),this, SLOT(connected()));
}


