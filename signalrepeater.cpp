#include "signalrepeater.h"
#include <QDebug>

//#include <mainmenu_widget.h>
SignalRepeater::SignalRepeater(MainWindowWidget *mainwindow):mainwindow(mainwindow){

    serverManager = new ServerManager;
}

SignalRepeater::~SignalRepeater()
{
    delete serverManager;
}

void SignalRepeater::gameStart()
{
//    qDebug() << "start game";
    GameWidget* game = new GameWidget(this, mainwindow);
    mainwindow->setWidget(game);
}

void SignalRepeater::exitToMenu() const
{
//    qDebug() << "exit to menu";
    MainMenuWidget* mainMenu = new MainMenuWidget(this, mainwindow);
    mainwindow->setWidget(mainMenu);
}

void SignalRepeater::openLocalhostMenu()
{
//    qDebug() << "open local host menu";
    LocalHostWidget* localHost = new LocalHostWidget(this, mainwindow);
    mainwindow->setWidget(localHost);
}


void SignalRepeater::aplicationClose() const
{
    qDebug() << "aplication close";
    mainwindow->close();
}

ServerManager* SignalRepeater::getServerManager()
{
    return serverManager;
}



//void SignalRepeater::setServerManager(const ServerManager* sm)
//{

//}
