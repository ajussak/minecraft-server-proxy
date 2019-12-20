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
    Client(QObject *parent, QTcpSocket *socket);

public slots:
    void readClient();

private:
    std::map<int, Packet*>* currentPackets;
    QTcpSocket* socket;
};


#endif //MINECRAFT_LAUNCH_PROXY_CLIENT_H
