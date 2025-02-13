#include "game_widget.h"

#include "QHBoxLayout"
#include "QVBoxLayout"
#include <QRandomGenerator>

//void function bot()
//{
//    int randomNumber = QRandomGenerator::global()->bounded(2);
//}

GameWidget::GameWidget(SignalRepeater* sr,QWidget *parent)
    : QWidget(parent)
{
    rockButton = new QPushButton("Камень",this);
    scissorsButton = new QPushButton("Ножницы",this);
    paperButton = new QPushButton("Бумага",this);

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(rockButton);
    hbox->addWidget(scissorsButton);
    hbox->addWidget(paperButton);


    firstPlayerReady = new QLabel("Ждем ход противника", this);
    secondPlayerReady = new QLabel("Противник сделал ход", this);

    serverDiconnect = new QLabel("Хост отлключился", this);
    clientDisconnect = new QLabel("Противник отлючился, ждем повторого подключения", this);



    exitToMenuButton = new QPushButton("Выйти в главное меню",this);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(firstPlayerReady);
    vbox->addWidget(secondPlayerReady);
    vbox->addWidget(serverDiconnect);
    vbox->addWidget(clientDisconnect);
    vbox->addLayout(hbox);
    vbox->addWidget(exitToMenuButton);

    serverManager = sr->getServerManager();
    connect(serverManager, ServerManager::clientDisconnectFromServer, this, GameWidget::clientDisconnectMessage);
    connect(serverManager, ServerManager::serverCloseForClient, this, GameWidget::serverDisconnectMessage);

    connect(exitToMenuButton,QPushButton::clicked, serverManager, ServerManager::closeServer);
    connect(exitToMenuButton,QPushButton::clicked, serverManager, ServerManager::closeConnection);

    gameProcess =  new GameProcess(serverManager);

    connect(rockButton, QPushButton::clicked, gameProcess, GameProcess::stoneChoosing);
    connect(scissorsButton, QPushButton::clicked, gameProcess, GameProcess::scissorsChoosing);
    connect(paperButton, QPushButton::clicked, gameProcess, GameProcess::paperChoosing);

    connect(exitToMenuButton, QPushButton::clicked, sr, SignalRepeater::exitToMenu);

    baseStateReturn();
}

void GameWidget::clientDisconnectMessage()
{
    clientDisconnect->show();
}

void GameWidget::serverDisconnectMessage()
{
    rockButton->setEnabled(false);
    scissorsButton->setEnabled(false);
    paperButton->setEnabled(false);

    serverDiconnect->show();
}

void GameWidget::waitEnemyMessage()
{
    firstPlayerReady->show();
}

void GameWidget::enemyWaitingMessage()
{
    secondPlayerReady->show();
}

void GameWidget::baseStateReturn()
{
    firstPlayerReady->hide();
    secondPlayerReady->hide();

    serverDiconnect->hide();
    clientDisconnect->hide();
}


GameWidget::~GameWidget()
{

}
