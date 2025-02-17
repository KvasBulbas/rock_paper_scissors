#ifndef GAMESERVER_H
#define GAMESERVER_H

//#include "signalrepeater.h"

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>


// Сервер
class Server : public QTcpServer {
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);

    void startServer(quint16 port) ;
    void sendMessageToClient(const QString &message);

signals:
    void clientDisconnect();
    void serverIsReady();
    void clientChoiceIsAccepted(int clientChoice);

private slots:
    void onNewConnection();

private:
    QTcpSocket* clientSocket = nullptr;

};

// Клиент
//class Client : public QObject {
//    Q_OBJECT

//public:
//    Client(QObject *parent = nullptr) : QObject(parent) {
//        connect(&socket, &QTcpSocket::connected, this, &Client::onConnected);
//        connect(&socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
//        connect(&socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
//    }

//    void connectToServer(const QString &host, quint16 port) {
//        socket.connectToHost(host, port);
//    }

//    void disconnectFromServer()
//    {
//        if(socket.state() == QAbstractSocket::ConnectedState)
//            socket.disconnectFromHost();
//    }

//    void sendMessage(const QString &message) {
//        if (socket.state() == QAbstractSocket::ConnectedState) {
//            socket.write(message.toUtf8());
//        } else {
//            qDebug() << "Не удалось отправить сообщение. Клиент не подключен.";
//        }
//    }

//    bool checkConnection()
//    {


//        return (socket.state() == QAbstractSocket::ConnectedState);
//    }


//signals:
//    void clientIsReady();
//    void serverCloseForClient();
//    void serverChoiceIsAccepted(int clientChoice);
//    void serverSendResult(int result);

//private slots:
//    void onConnected() {
//        emit clientIsReady();
//        qDebug() << "Подключено к серверу.";
//    }

//    void onReadyRead() {
//        QByteArray data = socket.readAll();




//        if(data.startsWith("game:"))
//        {
//            int serverChoice = data.mid(5).toInt();

////            qDebug() << "server choice: " << serverChoice;

//            emit serverChoiceIsAccepted(serverChoice);
//        }

//        if(data.startsWith("result:"))
//        {

//            qDebug() << "data: " << data;
//            int result = data.mid(7).toInt();

//            switch (result) {
//            case 0:
//                result = 2;
//                break;
//            case 2:
//                result = 0;
//            }

//            qDebug() << "result2: " << result;

//            emit serverSendResult(result);
//        }
//    }

//    void onDisconnected() {
//        qDebug() << "Server close";
//        emit serverCloseForClient();

//    }

//private:
//    QTcpSocket socket;
//};

#endif // GAMESERVER_H
