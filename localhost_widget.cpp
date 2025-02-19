#include "localhost_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QIntValidator>


AdressLineEdit::AdressLineEdit(AplicationManager *aplicationManager, QWidget *parent) : QWidget(parent)
{
    //создание виджетов
    hostLineEdit = new QLineEdit("127.0.0.1", this);
    portLineEdit = new QLineEdit("1234", this);
    colon = new QLabel(":", this);
    hostLineEdit->setMaximumWidth(100);
    portLineEdit->setMaximumWidth(50);


    QHBoxLayout* hbox = new QHBoxLayout(this);
    hbox->setSpacing(0);
    hbox->setContentsMargins(0, 0, 0, 0);

    //выравнивание виджетов
    hbox->addStretch(1);
    hbox->addWidget(hostLineEdit);
    hbox->addWidget(colon);
    hbox->addWidget(portLineEdit);
    hbox->addStretch(1);

    //устанавливаем валидатор, который позволяет вводить только числа от 0 до 99999 в поле с портом
    portLineEdit->setValidator(new QIntValidator(0, 99999, portLineEdit));

    serverManager = aplicationManager->getServerManager();//достаем serverManager, для использования его в слоте
}

void AdressLineEdit::enterServerName()
{
    //изымаем из полей ввода адрес и порт, который ввела пользователь
    const QString hostName = hostLineEdit->text();
    const quint16 port = portLineEdit->text().toUInt();

    //вызываем метод подключения к адресу
    serverManager->createConnection(hostName, port);
}


LocalHostWidget::LocalHostWidget(AplicationManager *aplicationManager, QWidget *parent): QWidget(parent)
{
    this->setFixedWidth(450);

    //создание виджетов
    createLobbyButton = new QPushButton("Создать лобби",this);
    createLobbyMesage = new QTextEdit(this);

    connectButton = new QPushButton("Подключиться напрямую",this);
    adressLineEdit = new AdressLineEdit(aplicationManager, this);
    connectionMesage = new QLabel("Подключение");

    exitToMenuButton = new QPushButton("Выйти в главное меню",this);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(createLobbyButton);
    vbox->addWidget(createLobbyMesage);
    vbox->addWidget(connectButton);
    vbox->addWidget(adressLineEdit);
    vbox->addWidget(connectionMesage);
    vbox->addWidget(exitToMenuButton);

    //скрываем сообщения, которые будут появляется при действиях пользователя
    createLobbyMesage->hide();
    connectionMesage->hide();


    serverManager = aplicationManager->getServerManager();//достаем servermanager для конектов

    //если клиенту удалось подключиться к серверу, то происходит запуск игры
    connect(serverManager, &ServerManager::connectionIsOk, aplicationManager, &AplicationManager::gameStart);

    //возвращаем виджет в изначальное состояния при нажатии на кнопку выхода или при нажатии на esc
    connect(exitToMenuButton, &QPushButton::clicked, this, &LocalHostWidget::baseStateReturn);
    connect(this, &LocalHostWidget::escPressed, this, &LocalHostWidget::baseStateReturn);

    //выходим в глвное меню при нажатии на кнопку выхода
    connect(exitToMenuButton, &QPushButton::clicked, aplicationManager, &AplicationManager::exitToMenu);

    //вызываем метод создания сервера при нажатии на кнопку
    connect(createLobbyButton, &QPushButton::clicked, this, &LocalHostWidget::createLobby);
    //вызываем метод создания подключения при нажатии на кнопку
    connect(connectButton , &QPushButton::clicked, this, &LocalHostWidget::clientConnect);

    //если сервер был создан вызываем метод, который покажет нам сообщение об этом
    connect(serverManager, &ServerManager::serverCreated, this, &LocalHostWidget::editCreatedMessage);

}

void LocalHostWidget::createLobby()//метод создания сервера
{
    serverManager->createServer();//создаем сервер
    createLobbyMesage->show();//показываем сообщние о создании сервера
    connectButton->setEnabled(false);//делаем кнопку подключения неактивной
}

//метод изменения сообщения о том, что сервер создан, и по каким адресам к нему пожно подключиться
void LocalHostWidget::editCreatedMessage(const QString& serverAdresses, const QString& port)
{
    createLobbyMesage->setText("К серверу можно подключиться по адресам: " + serverAdresses + "с портом: " +
    port + ", ожидание подключения");
}

void LocalHostWidget::clientConnect()//метод подключения клиента к серверу
{
    createLobbyButton->setEnabled(false);//делаем кнопку создания сервера неактивной
    adressLineEdit->enterServerName();//вызываем метод ввода адреса для подключения
    adressLineEdit->hide();
    connectionMesage->show();
}

//метод который возвращает виджет в изначальное состояние, а также закрывает сервер или закрываеи подключение
void LocalHostWidget::baseStateReturn()
{
    connectButton->setEnabled(true);
    createLobbyButton->setEnabled(true);
    createLobbyMesage->hide();
    connectionMesage->hide();
    serverManager->closeServer();//закрываем сервер
    serverManager->closeConnection();//закрываем подключение
    adressLineEdit->show();
}

LocalHostWidget::~LocalHostWidget()
{
//    baseStateReturn();
//    qDebug() <<  "localhost delete";
}
