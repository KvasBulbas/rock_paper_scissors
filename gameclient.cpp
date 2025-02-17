#include "gameclient.h"
#include <QCoreApplication>

Client::Client(QObject *parent) : QObject(parent) {
    connect(&socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
}

void Client::connectToServer(const QString &host, quint16 port) {
    socket.connectToHost(host, port);
}

void Client::disconnectFromServer()
{
    if(socket.state() == QAbstractSocket::ConnectedState)
    {
        socket.disconnectFromHost();
        socket.flush();
        QCoreApplication::processEvents();
    }
}

void Client::sendMessage(const QString &message) {
    if (socket.state() == QAbstractSocket::ConnectedState) {
        socket.write(message.toUtf8());
        socket.flush();
    } else {
        qDebug() << "Не удалось отправить сообщение. Клиент не подключен.";
    }
}



void Client::onConnected() {
    emit clientIsReady();
    qDebug() << "Подключено к серверу.";
}

void Client::onReadyRead() {
    QByteArray data = socket.readAll();

    if(data.startsWith("game:"))
    {
        int serverChoice = data.mid(5).toInt();
        qDebug() << "server choice accepted";


        emit serverChoiceIsAccepted(serverChoice);
    }

    if(data.startsWith("result:"))
    {

//        qDebug() << "data: " << data;
        int result = data.mid(7).toInt();

        switch (result) {
        case 0:
            result = 2;
            break;
        case 2:
            result = 0;
        }

        qDebug() << "result accepeted " << result;

        emit serverSendResult(result);
    }
}

void Client::onDisconnected() {
    qDebug() << "Server close";
    emit serverCloseForClient();

}
