#include <QtCore/QCoreApplication>
#include "FakeMinecraftServer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    FakeMinecraftServer server;

    return a.exec();
}
