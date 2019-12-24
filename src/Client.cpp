//
// Created by adrien on 17/12/19.
//

#include "Client.h"
#include "PacketRegistry.h"


Client::Client(QObject *parent, QTcpSocket *socket, const QString &ip, int port) : QObject(parent), socket(socket) {
    bridged = true;
    currentPackets = nullptr;

    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(&remoteServerSocket, SIGNAL(readyRead()), this, SLOT(readRemoteServer()));

    remoteServerSocket.connectToHost(ip, port);

    if (!remoteServerSocket.waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
    }

}

void Client::readClient() {
    QDataStream socketStream(socket);

    try {

        forever {
            if (socket->bytesAvailable() <= 0)
                break;

            qint32 size = Packet::readVarInt(&socketStream); //Packet size

            QByteArray packetData = socket->read(size);
            QDataStream packetDataStream(packetData);

            if (bridged) {
                QByteArray sizeData;
                QDataStream sizeOutput(&sizeData, QIODevice::ReadWrite);

                Packet::writeVarInt(size, &sizeOutput);

                remoteServerSocket.write(sizeData);
                remoteServerSocket.write(packetData);
                remoteServerSocket.flush();
            } else {
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

    }
    catch (std::exception& e) {
        socket->disconnect();
        remoteServerSocket.disconnect();
    }
}


void Client::sendPacket(Packet *packet) {
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
    }
}

void Client::readRemoteServer() {
    QDataStream socketStream(&remoteServerSocket);

    try {
        forever {
            if (remoteServerSocket.bytesAvailable() <= 0)
                break;

            qint32 size = Packet::readVarInt(&socketStream); //Packet size

            QByteArray packetData = remoteServerSocket.read(size);

            if (bridged) {
                QByteArray sizeData;
                QDataStream sizeOutput(&sizeData, QIODevice::ReadWrite);

                Packet::writeVarInt(size, &sizeOutput);

                socket->write(sizeData);
                socket->write(packetData);
                socket->flush();
            }
        }
    } catch (std::exception& e) {
        socket->disconnect();
        remoteServerSocket.disconnect();
    }
}


