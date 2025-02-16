#include "game_widget.h"

#include "QHBoxLayout"
#include "QVBoxLayout"
#include <QRandomGenerator>
#include <Qtimer>
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


    youLose = new QLabel("Вы проиграли");
    youWin = new QLabel("Вы выиграли");
    draw = new QLabel("Ничья");



    resultWidget = new QStackedWidget(this);
    resultWidget->addWidget(youLose);
    resultWidget->addWidget(draw);
    resultWidget->addWidget(youWin);



    exitToMenuButton = new QPushButton("Выйти в главное меню",this);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(resultWidget);
    vbox->addWidget(firstPlayerReady);
    vbox->addWidget(secondPlayerReady);
    vbox->addWidget(serverDiconnect);
    vbox->addWidget(clientDisconnect);
    vbox->addLayout(hbox);
    vbox->addWidget(exitToMenuButton);


    serverManager = sr->getServerManager();

    connect(serverManager, ServerManager::clientDisconnectFromServer, this, GameWidget::clientDisconnectMessage);
    connect(serverManager, ServerManager::serverCloseForClient, this, GameWidget::serverDisconnectMessage);
    connect(serverManager, ServerManager::clientChoiceIsAccepted, this, GameWidget::enemyWaitingMessage);
    connect(serverManager, ServerManager::serverChoiceIsAccepted, this, GameWidget::enemyWaitingMessage);
    connect(serverManager, ServerManager::resultIsAccepted, this, GameWidget::setResult);

    connect(exitToMenuButton,QPushButton::clicked, serverManager, ServerManager::closeServer);
    connect(exitToMenuButton,QPushButton::clicked, serverManager, ServerManager::closeConnection);


    gameProcess =  new GameProcess(serverManager);

    connect(rockButton, QPushButton::clicked, gameProcess, GameProcess::stoneChoosing);
    connect(scissorsButton, QPushButton::clicked, gameProcess, GameProcess::scissorsChoosing);
    connect(paperButton, QPushButton::clicked, gameProcess, GameProcess::paperChoosing);

    connect(rockButton, QPushButton::clicked, this, GameWidget::waitEnemyMessage);
    connect(scissorsButton, QPushButton::clicked, this, GameWidget::waitEnemyMessage);
    connect(paperButton, QPushButton::clicked, this, GameWidget::waitEnemyMessage);




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

void GameWidget::enemyWaitingMessage(int choice)
{
    Q_UNUSED(choice);
    secondPlayerReady->show();
    qDebug() << "wait enemy";
}

void GameWidget::baseStateReturn()
{
    firstPlayerReady->hide();
    secondPlayerReady->hide();

    serverDiconnect->hide();
    clientDisconnect->hide();

    resultWidget->hide();
    rockButton->setEnabled(true);
    scissorsButton->setEnabled(true);
    paperButton->setEnabled(true);
}

void GameWidget::setResult(int result)
{
    baseStateReturn();
    resultWidget->setCurrentIndex(result);
    resultWidget->show();


    rockButton->setEnabled(false);
    scissorsButton->setEnabled(false);
    paperButton->setEnabled(false);

    QTimer::singleShot(3000, [this]() {
        baseStateReturn();
    });
}


GameWidget::~GameWidget()
{
    delete gameProcess;
}
