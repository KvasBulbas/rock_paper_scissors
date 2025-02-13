#include "localhost_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>

LocalHostWidget::LocalHostWidget(SignalRepeater *sr, QWidget *parent): QWidget(parent)
{
    createLobbyButton = new QPushButton("Создать лобби",this);
    findLobbyButton = new QPushButton("Найти лобби",this);
    connectButton = new QPushButton("Подключиться напрямую",this);
    exitToMenuButton = new QPushButton("Выйти в главное меню",this);

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(createLobbyButton);
    vbox->addWidget(findLobbyButton);
    vbox->addWidget(connectButton);
    vbox->addWidget(exitToMenuButton);

    createLobbyMesage = new QLabel("Сервер создан, ожидание другого игрока");
    connectionMesage = new QLabel("Подключение");
    createLobbyMesage->hide();
    connectionMesage->hide();

    QVBoxLayout* msgBox = new QVBoxLayout();
    msgBox->addWidget(createLobbyMesage);
    msgBox->addWidget(connectionMesage);

    QHBoxLayout* hbox = new QHBoxLayout(this);
    hbox->addLayout(vbox);
    hbox->addLayout(msgBox);

    serverManager = sr->getServerManager();
    connect(serverManager, ServerManager::connectionIsOk, sr, SignalRepeater::gameStart);

    connect(exitToMenuButton, QPushButton::clicked, sr, SignalRepeater::exitToMenu);
    connect(createLobbyButton, QPushButton::clicked, this, LocalHostWidget::createLobby);
    connect(connectButton , QPushButton::clicked, this, LocalHostWidget::clientConnect);

    connect(exitToMenuButton, QPushButton::clicked, this, LocalHostWidget::baseStateReturn);
    connect(this, LocalHostWidget::escPressed, this, LocalHostWidget::baseStateReturn);
}

void LocalHostWidget::createLobby()
{
    serverManager->createServer();
    createLobbyMesage->show();
    findLobbyButton->setEnabled(false);
    connectButton->setEnabled(false);
}

void LocalHostWidget::clientConnect()
{
    createLobbyButton->setEnabled(false);
    serverManager->createConnection();
    connectionMesage->show();
}

void LocalHostWidget::baseStateReturn()
{
    findLobbyButton->setEnabled(true);
    connectButton->setEnabled(true);
    createLobbyButton->setEnabled(true);
    createLobbyMesage->hide();
    connectionMesage->hide();
    serverManager->closeServer();
    serverManager->closeConnection();
}

LocalHostWidget::~LocalHostWidget()
{
//    baseStateReturn();
//    qDebug() <<  "localhost delete";
}
