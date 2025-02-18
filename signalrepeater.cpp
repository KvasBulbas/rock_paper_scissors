#include "signalrepeater.h"
#include <QDebug>

AplicationManager::AplicationManager(MainWindowWidget *mainwindow):mainwindow(mainwindow){

    serverManager = new ServerManager;
}

AplicationManager::~AplicationManager()
{
    delete serverManager;
}

void AplicationManager::gameStart()//меняет виджет в главном окне на виджет самой игры
{
    GameWidget* game = new GameWidget(this, mainwindow);
    mainwindow->setWidget(game);
}

void AplicationManager::exitToMenu()//меняет виджет в главном окне на главное меню
{
    MainMenuWidget* mainMenu = new MainMenuWidget(this, mainwindow);
    mainwindow->setWidget(mainMenu);
}

void AplicationManager::openLocalhostMenu()//меняет виджет в главном окне на меню подключения
{
    LocalHostWidget* localHost = new LocalHostWidget(this, mainwindow);
    mainwindow->setWidget(localHost);
}


void AplicationManager::aplicationClose()//закрывает приложение
{
    mainwindow->close();
}

ServerManager* AplicationManager::getServerManager()//предоставляет объект ServerMangaer
{
    return serverManager;
}

