#include "localhost_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QIntValidator>


AdressLineEdit::AdressLineEdit(AplicationManager *aplicationManager, QWidget *parent) : QWidget(parent)
{
    hostLineEdit = new QLineEdit("127.0.0.1", this);
    portLineEdit = new QLineEdit("1234", this);
    colon = new QLabel(":", this);
    hostLineEdit->setMaximumWidth(100);
    portLineEdit->setMaximumWidth(50);


    QHBoxLayout* hbox = new QHBoxLayout(this);
    hbox->setSpacing(0);  // Убираем расстояние между виджетами
    hbox->setContentsMargins(0, 0, 0, 0);  // Убираем внешние отступы

    hbox->addStretch(1);
    hbox->addWidget(hostLineEdit);
    hbox->addWidget(colon);
    hbox->addWidget(portLineEdit);
    hbox->addStretch(1);

    portLineEdit->setValidator(new QIntValidator(0, 99999, portLineEdit));

    serverManager = aplicationManager->getServerManager();
}

void AdressLineEdit::enterServerName()
{
    const QString hostName = hostLineEdit->text();
    const quint16 port = portLineEdit->text().toUInt();
    serverManager->createConnection(hostName, port);
}


LocalHostWidget::LocalHostWidget(AplicationManager *aplicationManager, QWidget *parent): QWidget(parent)
{
    createLobbyButton = new QPushButton("Создать лобби",this);
    createLobbyMesage = new QLabel("Сервер создан, ожидание другого игрока");

    connectButton = new QPushButton("Подключиться напрямую",this);
    adressLineEdit = new AdressLineEdit(aplicationManager, this);
    connectionMesage = new QLabel("Подключение");

    exitToMenuButton = new QPushButton("Выйти в главное меню",this);

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(createLobbyButton);
    vbox->addWidget(createLobbyMesage);
    vbox->addWidget(connectButton);
    vbox->addWidget(adressLineEdit);
    vbox->addWidget(connectionMesage);
    vbox->addWidget(exitToMenuButton);

    createLobbyMesage->hide();
    connectionMesage->hide();
    adressLineEdit->hide();

    QHBoxLayout* hbox = new QHBoxLayout(this);
    hbox->addLayout(vbox);

    serverManager = aplicationManager->getServerManager();
    connect(serverManager, ServerManager::connectionIsOk, aplicationManager, AplicationManager::gameStart);

    connect(exitToMenuButton, QPushButton::clicked, aplicationManager, AplicationManager::exitToMenu);
    connect(createLobbyButton, QPushButton::clicked, this, LocalHostWidget::createLobby);
    connect(connectButton , QPushButton::clicked, this, LocalHostWidget::showAdressLineEdit);

    connect(exitToMenuButton, QPushButton::clicked, this, LocalHostWidget::baseStateReturn);
    connect(this, LocalHostWidget::escPressed, this, LocalHostWidget::baseStateReturn);

}

void LocalHostWidget::createLobby()
{
    serverManager->createServer();
    createLobbyMesage->show();
    connectButton->setEnabled(false);
}

void LocalHostWidget::showAdressLineEdit()
{
    createLobbyButton->setEnabled(false);

    adressLineEdit->show();
    connect(this, LocalHostWidget::enterPressed, this, LocalHostWidget::clientConnect);
}

void LocalHostWidget::clientConnect()
{
    disconnect(this, LocalHostWidget::enterPressed, this, LocalHostWidget::clientConnect);
    connectButton->setEnabled(false);
    adressLineEdit->enterServerName();
    adressLineEdit->hide();

    connectionMesage->show();
}


void LocalHostWidget::baseStateReturn()
{
    connectButton->setEnabled(true);
    createLobbyButton->setEnabled(true);
    createLobbyMesage->hide();
    connectionMesage->hide();
    serverManager->closeServer();
    serverManager->closeConnection();
    adressLineEdit->hide();
    disconnect(this, LocalHostWidget::enterPressed, this, LocalHostWidget::clientConnect);
}

LocalHostWidget::~LocalHostWidget()
{
//    baseStateReturn();
//    qDebug() <<  "localhost delete";
}
