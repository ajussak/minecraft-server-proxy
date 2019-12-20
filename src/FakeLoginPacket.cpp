//
// Created by adrien on 19/12/19.
//

#include "FakeLoginPacket.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QtCore/QProcess>

void FakeLoginPacket::fromData(QDataStream *stream) {
    qDebug() << Packet::readString(stream);
}

void FakeLoginPacket::handle(QTcpSocket *socket) {
    if(process->state() == QProcess::NotRunning) {
        QJsonObject jsonObject;

        jsonObject.insert("text", QJsonValue("Server starting request sent (Please wait 2 minutes)"));
        jsonDocument = new QJsonDocument(jsonObject);

        process->start("/home/adrien/start.sh");
    }
}

void FakeLoginPacket::toData(QDataStream *stream) {
    Packet::writeVarInt(0x00, stream);
    QByteArray byteArray = jsonDocument->toJson();

    writeVarInt(byteArray.size(), stream);
    for(qint8 b : byteArray)
        *stream << b;
}

FakeLoginPacket::~FakeLoginPacket() {
    delete jsonDocument;
    delete process;
}

FakeLoginPacket::FakeLoginPacket() {
    process = new QProcess();
}
