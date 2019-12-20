//
// Created by adrien on 17/12/19.
//

#include "StatusRequestPacket.h"
#include <QJsonObject>
#include <QJsonArray>


StatusRequestPacket::~StatusRequestPacket()
{
    delete jsonDocument;
}

void StatusRequestPacket::fromData(QDataStream *stream) {

}

void StatusRequestPacket::handle(QTcpSocket *socket) {
    QJsonObject jsonObject;

    QJsonObject versionObject;
    versionObject.insert("name", QJsonValue("1.15.1"));
    versionObject.insert("protocol", QJsonValue(575));

    QJsonObject descriptionObject;
    descriptionObject.insert("text", "Minecraft ETIQ (En pause)");

    QJsonObject playersObject;
    playersObject.insert("max", QJsonValue(0));
    playersObject.insert("online", QJsonValue(0));
    playersObject.insert("sample", QJsonArray());

    jsonObject.insert("version", versionObject);
    jsonObject.insert("description", descriptionObject);
    jsonObject.insert("players", playersObject);

    jsonDocument = new QJsonDocument(jsonObject);
}

void StatusRequestPacket::toData(QDataStream *stream) {
    QByteArray byteArray = jsonDocument->toJson();

    writeVarInt(0, stream);
    writeVarInt(byteArray.size(), stream);
    for(qint8 b : byteArray)
        *stream << b;
}

