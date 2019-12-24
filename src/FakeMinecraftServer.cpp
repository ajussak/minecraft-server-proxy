//
// Created by adrien on 17/12/19.
//

#include <QtCore/QDataStream>
#include "FakeMinecraftServer.h"
#include "Packet.h"
#include "PacketRegistry.h"
#include "StatusRequestPacket.h"
#include "PingPacket.h"
#include "FakeLoginPacket.h"

FakeMinecraftServer::FakeMinecraftServer(QObject *parent) : QObject(parent) {
    server = new QTcpServer(this);

    PacketRegistry::getInstance().registerPacket(1, 0x00, new StatusRequestPacket());
    PacketRegistry::getInstance().registerPacket(1, 0x01, new PingPacket());
    PacketRegistry::getInstance().registerPacket(2, 0x00, new FakeLoginPacket());

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any, 25565)) {
        qDebug() << "Server could not start";
    } else {
        qDebug() << "Server started!";
    }
}

FakeMinecraftServer::~FakeMinecraftServer() {
    delete server;

    for (auto &client : clients) {
        delete client;
    }
}

void FakeMinecraftServer::newConnection() {
    QTcpSocket *socket = server->nextPendingConnection();

    auto *client = new Client(this, socket, "mc.hypixel.net", 25565);

    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));

    clients.push_back(client);
}

void FakeMinecraftServer::disconnected() {
    auto* client = dynamic_cast<Client *>(sender());
    clients.remove(client);
    delete client;
}

