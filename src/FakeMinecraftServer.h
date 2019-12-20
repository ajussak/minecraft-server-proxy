//
// Created by adrien on 17/12/19.
//

#ifndef MINECRAFT_LAUNCH_PROXY_FAKEMINECRAFTSERVER_H
#define MINECRAFT_LAUNCH_PROXY_FAKEMINECRAFTSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include "Client.h"

class FakeMinecraftServer : public QObject {
    Q_OBJECT
public:
    explicit FakeMinecraftServer(QObject *parent = 0);
    ~FakeMinecraftServer() override;

public slots:
    void newConnection();

private:
    QTcpServer *server;
    std::list<Client*> clients;
};


#endif //MINECRAFT_LAUNCH_PROXY_FAKEMINECRAFTSERVER_H
