//
// Created by adrien on 17/12/19.
//

#include "Packet.h"

#include <QDebug>

qint32 Packet::readVarInt(QDataStream *stream) {
    qint32 numRead = 0;
    qint32 result = 0;
    qint8 read;
    do {
        *stream >> read;
        int value = (read & 0b01111111);
        result |= (value << (7 * numRead));

        numRead++;
        if (numRead > 5) {
            throw std::length_error("VarInt is too big");
        }
    } while ((read & 0b10000000) != 0);

    return result;
}

qint64 Packet::readVarLong(QDataStream *stream) {
    qint32 numRead = 0;
    qint64 result = 0;
    qint8 read;
    do {
        *stream >> read;
        qint32 value = (read & 0b01111111);
        result |= (value << (7 * numRead));

        numRead++;
        if (numRead > 10) {
            throw std::length_error("VarLong is too big");
        }
    } while ((read & 0b10000000) != 0);

    return result;
}

QString Packet::readString(QDataStream *stream) {
    qint32 size = readVarInt(stream);

    QByteArray array;

    for (int i = 0; i < size; i++) {
        qint8 b;
        *stream >> b;
        array.append(b);
    }

    return QString(array);
}

qint32 Packet::writeVarInt(qint32 value, QDataStream *stream) {
    int i = 0;
    do {
        qint8 temp = (qint8)(value & 0b01111111);
        // Note: >>> means that the sign bit is shifted with the rest of the number rather than being left alone
        value >>= 7;
        if (value != 0) {
            temp |= 0b10000000;
        }
        *stream << temp;
        i++;
    } while (value != 0);
    return i;
}

qint32 Packet::writeVarLong(qint64 value, QDataStream *stream) {
    int i = 0;
    do {
        qint8 temp = (qint8)(value & 0b01111111);
        // Note: >>> means that the sign bit is shifted with the rest of the number rather than being left alone
        value >>= 7;
        if (value != 0) {
            temp |= 0b10000000;
        }
        *stream << temp;
        i++;
    } while (value != 0);
    return  i;
}

void Packet::writeString(QString s, QDataStream *stream) {
    QByteArray byteArray = s.toUtf8();

    writeVarInt(byteArray.size(), stream);
    for(qint8 b : byteArray)
        *stream << b;
}

