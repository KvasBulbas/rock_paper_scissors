#include "gameclient.h"
#include <QCoreApplication>


Client::Client()
{
    connect(this, &QTcpSocket::connected, this, &Client::onConnected);//при подключении клмента вызывается метод
    connect(this, &QTcpSocket::readyRead, this, &Client::onReadyRead);//при чтении данных вызывается метод
    connect(this, &QTcpSocket::disconnected, this, &Client::onDisconnected);//при закрытии сервера вызывается метод
}

void Client::connectToServer(const QString &host, quint16 port)//метод подключения клмента к серверу
{
    this->connectToHost(host, port);
}

void Client::disconnectFromServer()//метод отключения клинта от сервера
{
    if(this->state() == QAbstractSocket::ConnectedState)
    {
        this->disconnectFromHost();
        this->flush();
        QCoreApplication::processEvents();
    }
}

void Client::sendMessage(const QString &message)//метод отправки ссообщения серверу
{
    if (this->state() == QAbstractSocket::ConnectedState)//если подключение в норме, то отправляем сообщеение
    {
        this->write(message.toUtf8());
        this->flush();
    }
    else
    {
        qDebug() << "Wrong connection";
    }
}



void Client::onConnected()//метод срабатывающий при подключении клиента к серверу
{
    emit clientIsReady();//оповещаем о том, что подключение прошло успешно
    qDebug() << "Connection sucsessful";
}

void Client::onReadyRead()//метод срабатывающий при чтении данных от сервера
{
    QByteArray data = this->readAll();//достаем данные

    if(data.startsWith("game:"))//если сообщение пришло об игре
    {
        int serverChoice = data.mid(5).toInt();
        emit serverChoiceIsAccepted(serverChoice);//оповещаем, что сервер сделал выбор и ждет выбора клмента
    }

    if(data.startsWith("result:"))//если пришел результат
    {
        int result = data.mid(7).toInt();

        switch (result) {//если сервер оповещает, что он выиграл, то полкчается клмиент проиграл, и наоборот, поэтому меняем результат для клиента
        case 0:
            result = 2;
            break;
        case 2:
            result = 0;
        }

        emit serverSendResult(result);//оповещаем о том, то клмент отправил результат
    }
}

void Client::onDisconnected()//метод срабатывающий при закрытии сервера
{
    qDebug() << "Server close";
    emit serverCloseForClient();

}

//Client::Client(QObject *parent) : QObject(parent)
//{
//    connect(&socket, &QTcpSocket::connected, this, &Client::onConnected);
//    connect(&socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
//    connect(&socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
//}

//void Client::connectToServer(const QString &host, quint16 port)
//{
//    socket.connectToHost(host, port);
//}

//void Client::disconnectFromServer()
//{
//    if(socket.state() == QAbstractSocket::ConnectedState)
//    {
//        socket.disconnectFromHost();
//        socket.flush();
//        QCoreApplication::processEvents();
//    }
//}

//void Client::sendMessage(const QString &message)
//{
//    if (socket.state() == QAbstractSocket::ConnectedState)
//    {
//        socket.write(message.toUtf8());
//        socket.flush();
//    } else
//    {
//        qDebug() << "Wrong connection";
//    }
//}



//void Client::onConnected()
//{
//    emit clientIsReady();
//    qDebug() << "Connection sucsessful";
//}

//void Client::onReadyRead()
//{
//    QByteArray data = socket.readAll();

//    if(data.startsWith("game:"))
//    {
//        int serverChoice = data.mid(5).toInt();
//        emit serverChoiceIsAccepted(serverChoice);
//    }

//    if(data.startsWith("result:"))
//    {
//        int result = data.mid(7).toInt();

//        switch (result) {
//        case 0:
//            result = 2;
//            break;
//        case 2:
//            result = 0;
//        }

//        emit serverSendResult(result);
//    }
//}

//void Client::onDisconnected()
//{
//    qDebug() << "Server close";
//    emit serverCloseForClient();

//}
