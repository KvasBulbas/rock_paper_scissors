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
    Server(QObject *parent = nullptr) : QTcpServer(parent) {
        connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);
    }

    void startServer(quint16 port) {
        if (this->listen(QHostAddress::Any, port)) {
            qDebug() << "Start server" << port;
        } else {
            qDebug() << "Start server: error" << this->errorString();
        }
    }


    void setServerChoice(int choice)
    {
        if(0 <= choice && choice <=2)
            serverChoice = choice;

        if(clientChoice != -1)
            getResult();

    }

signals:
    void serverIsReady();

private slots:
    void onNewConnection() {
        QTcpSocket *clientSocket = this->nextPendingConnection();
        qDebug() << "New connection:" << clientSocket->peerAddress().toString();

          connect(clientSocket, &QTcpSocket::readyRead, [this,clientSocket]() {
              QByteArray data = clientSocket->readAll();
//              qDebug() << "Сообщение от клиента:" << data;
//              clientSocket->write("soobshenie polucheno: " + data);

              if(data.startsWith("game:"))
              {
                  clientChoice = data.mid(5).toInt(); // Число от клиента
                  qDebug() << "Число клиента:" << clientChoice;

                  if(serverChoice != -1)
                    getResult();
              }


          });

        connect(clientSocket, &QTcpSocket::disconnected, [clientSocket]() {
            qDebug() << "Клиент отключился:" << clientSocket->peerAddress().toString();
                                                                    clientSocket->deleteLater();
        });

        emit serverIsReady();
    }






    void getResult()
    {
        qDebug() << "SC: " << serverChoice << " CC: " << clientChoice;
    }
//    void sendMessage(const QString &message)
//    {
//        QTcpSocket *clientSocket = this->nextPendingConnection();
//        clientSocket->write()
//    }

private:
    int serverChoice = -1;
    int clientChoice = -1;
};

// Клиент
class Client : public QObject {
    Q_OBJECT

public:
    Client(QObject *parent = nullptr) : QObject(parent) {
        connect(&socket, &QTcpSocket::connected, this, &Client::onConnected);
        connect(&socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
        connect(&socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    }

    void connectToServer(const QString &host, quint16 port) {
        socket.connectToHost(host, port);
    }

    void disconnectFromServer()
    {
        if(socket.state() == QAbstractSocket::ConnectedState)
            socket.disconnectFromHost();
    }

    void sendMessage(const QString &message) {
        if (socket.state() == QAbstractSocket::ConnectedState) {
            socket.write(message.toUtf8());
        } else {
            qDebug() << "Не удалось отправить сообщение. Клиент не подключен.";
        }
    }

    bool checkConnection()
    {

        return (socket.state() == QAbstractSocket::ConnectedState);
    }


signals:
    void clientIsReady();


private slots:
    void onConnected() {
        emit clientIsReady();
        qDebug() << "Подключено к серверу.";
    }

    void onReadyRead() {
        QByteArray data = socket.readAll();
        qDebug() << "Сообщение от сервера:" << data;
    }

    void onDisconnected() {
        qDebug() << "Отключено от сервера.";
    }

private:
    QTcpSocket socket;
};

#endif // GAMESERVER_H
