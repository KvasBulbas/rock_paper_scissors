#ifndef GAMESERVER_H
#define GAMESERVER_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class GameServer : public QTcpServer {
    Q_OBJECT
public:
    GameServer(QObject* parent = nullptr) : QTcpServer(parent) {}

    void startServer(quint16 port) {
        if (listen(QHostAddress::Any, port)) {
            qDebug() << "Server started on port" << port;
        } else {
            qDebug() << "Server failed to start!";
        }
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket* clientSocket = new QTcpSocket(this);
        clientSocket->setSocketDescriptor(socketDescriptor);

        qDebug() << "New client connected: " << clientSocket->peerAddress().toString();

        connect(clientSocket, &QTcpSocket::readyRead, this, [clientSocket]() {
            QByteArray data = clientSocket->readAll();
            qDebug() << "Received data:" << data;

            // Эхо-ответ
            clientSocket->write("Server received: " + data);
        });

        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    }
};

#endif // GAMESERVER_H
