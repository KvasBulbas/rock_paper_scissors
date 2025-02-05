#include "mainwindow_widget.h"
#include "gameserver.h"
#include "gameclient.h"

#include <Qtimer>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowWidget w;
    w.show();


    GameServer server;
    server.startServer(1234);


    GameClient client;
    client.connectToServer("127.0.0.1", 1234);

    QTimer::singleShot(2000, [&client]() {
        client.sendData("Hello, Server!");
    });

    return a.exec();
}
