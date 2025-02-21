#include "game_widget.h"

#include "QHBoxLayout"
#include "QVBoxLayout"
#include <QRandomGenerator>
#include <QTimer>

GameWidget::GameWidget(AplicationManager* aplicationManager,QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(350,100);

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

    serverManager = aplicationManager->getServerManager();//достаем servermanager

    //при оповещении о том, что клиент отключился от сервера, вызываем соотвествеющий метод, отображающий информацию на экран
    connect(serverManager, &ServerManager::clientDisconnectFromServer, this, &GameWidget::clientDisconnectMessage);
    //при оповещении о том, что сервер закрылся, вызываем соотвествеющий метод, отображающий информацию на экран
    connect(serverManager, &ServerManager::serverCloseForClient, this, &GameWidget::serverDisconnectMessage);

    //при оповещении о том, что клмент сделал выбор, вызываем соотвествеющий метод, отображающий информацию на экран
    connect(serverManager, &ServerManager::clientChoiceIsAccepted, this, &GameWidget::enemyWaitingMessage);
    //при оповещении о том, что сервер сделал выбор, вызываем соотвествеющий метод, отображающий информацию на экран
    connect(serverManager, &ServerManager::serverChoiceIsAccepted, this, &GameWidget::enemyWaitingMessage);
    //при оповещении о том, что резултат пришел, вызываем соотвествеющий метод, отображающий результат игры
    connect(serverManager, &ServerManager::resultIsAccepted, this, &GameWidget::setResult);

    //подключаем кнопки отключения сервера или клмента при выходе из игры
    connect(exitToMenuButton,&QPushButton::clicked, serverManager, &ServerManager::closeServer);
    connect(exitToMenuButton,&QPushButton::clicked, serverManager, &ServerManager::closeConnection);

    //создаем объект обработчика игры
    gameProcess =  new GameProcess(serverManager);

    //при при нажатии кнопок ходов игрока, вызываеются соответсвющие методы в данном классе, отображающие информацию на экран
    connect(rockButton, &QPushButton::clicked, this, &GameWidget::waitEnemyMessage);
    connect(scissorsButton, &QPushButton::clicked, this, &GameWidget::waitEnemyMessage);
    connect(paperButton, &QPushButton::clicked, this, &GameWidget::waitEnemyMessage);

    //при при нажатии кнопок ходов игрока, вызываеются соответсвющие сигналы в классе gameprocess
    connect(rockButton, &QPushButton::clicked, gameProcess, &GameProcess::stoneChoosing);
    connect(scissorsButton, &QPushButton::clicked, gameProcess, &GameProcess::scissorsChoosing);
    connect(paperButton, &QPushButton::clicked, gameProcess, &GameProcess::paperChoosing);

    connect(exitToMenuButton, &QPushButton::clicked, aplicationManager, &AplicationManager::exitToMenu);//подключаем кнопку выхода в главное меню

    baseStateReturn();//вызываем метод возвраащающий виджет в базовое состояние
}

void GameWidget::clientDisconnectMessage()//метод выводящий сообщение о том, что клмент отключился
{
    baseStateReturn();
    //отключаем кнопки для избежаний софтлока
    rockButton->setEnabled(false);
    scissorsButton->setEnabled(false);
    paperButton->setEnabled(false);
    clientDisconnect->show();
}

void GameWidget::serverDisconnectMessage()//метод выводящий сообщение о том, что сервер закрылся
{
    baseStateReturn();
    //отключаем кнопки для избежаний софтлока
    rockButton->setEnabled(false);
    scissorsButton->setEnabled(false);
    paperButton->setEnabled(false);

    serverDiconnect->show();
}

void GameWidget::waitEnemyMessage()//метод выводящий сообщение о ожидании противника
{
    if(!reslutOk)//если резултат не пришел
        firstPlayerReady->show();
}

void GameWidget::enemyWaitingMessage(int choice)//метод выводящий сообщение о том, что противкник сделал выбор
{
    Q_UNUSED(choice);
    if(!reslutOk)//если результат не пришел
        secondPlayerReady->show();
}

void GameWidget::baseStateReturn()//метод скрывающий все сообщения и отменящий все действия, возращающий виджет в изначальное состояние
{
    firstPlayerReady->hide();
    secondPlayerReady->hide();

    serverDiconnect->hide();
    clientDisconnect->hide();

    resultWidget->hide();
    rockButton->setEnabled(true);
    scissorsButton->setEnabled(true);
    paperButton->setEnabled(true);
    exitToMenuButton->setEnabled(true);
    reslutOk = false;
}

void GameWidget::setResult(int result)//метод смены и отображения резльутата в виджете
{
    baseStateReturn();

    reslutOk = true;
    resultWidget->setCurrentIndex(result);
    resultWidget->show();

    //отключаем кнопки для избежаний софтлока
    rockButton->setEnabled(false);
    scissorsButton->setEnabled(false);
    paperButton->setEnabled(false);
    exitToMenuButton->setEnabled(false);

    //выжидаем немного времени для того, чтобы игроки успели ознакомиться с резултатом игры, после чего возращаем виджет в базовое состояние
    QTimer::singleShot(1800, [this]() {
        baseStateReturn();
    });
}

GameWidget::~GameWidget()
{
    delete gameProcess;
}
