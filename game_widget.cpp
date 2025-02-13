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

    exitToMenuButton = new QPushButton("Выйти в главное меню",this);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(firstPlayerReady);
    vbox->addWidget(secondPlayerReady);
    vbox->addLayout(hbox);
    vbox->addWidget(exitToMenuButton);

//    connect(rockButton, QPushButton::clicked, , );
//    connect(scissorsButton, QPushButton::clicked, , );
//    connect(paperButton, QPushButton::clicked, , );

    serverManager = sr->getServerManager();


    connect(exitToMenuButton,QPushButton::clicked, serverManager, ServerManager::closeServer);
    connect(exitToMenuButton,QPushButton::clicked, serverManager, ServerManager::closeConnection);
    connect(exitToMenuButton, QPushButton::clicked, sr, SignalRepeater::exitToMenu);

}

void GameWidget::showMessage()
{

}


GameWidget::~GameWidget()
{

}
