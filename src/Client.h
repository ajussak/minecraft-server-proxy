//
// Created by adrien on 17/12/19.
//

#ifndef MINECRAFT_LAUNCH_PROXY_CLIENT_H
#define MINECRAFT_LAUNCH_PROXY_CLIENT_H

#include <QObject>
#include "Packet.h"
#include <QTcpSocket>

class Client : public QObject {
    Q_OBJECT

public:
    Client(QObject *parent, QTcpSocket *socket, const QString& ip, int port);
    void sendPacket(Packet* packet);

public slots:
    void readClient();
    void readRemoteServer();

signals:
    void disconnected();
    void startServer();
    void serverStateRequest();

private:
    std::map<int, Packet*>* currentPackets;
    QTcpSocket* socket;
    QTcpSocket remoteServerSocket;
    bool bridged;
};


#endif //MINECRAFT_LAUNCH_PROXY_CLIENT_H
