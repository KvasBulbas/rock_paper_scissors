#ifndef GAMECLIENT_H
#define GAMECLIENT_H


#include <QTcpSocket>
#include <QDebug>

class GameClient : public QObject {
    Q_OBJECT
public:
    GameClient(QObject* parent = nullptr) : QObject(parent) {
        socket = new QTcpSocket(this);

        connect(socket, &QTcpSocket::readyRead, this, [this]() {
            QByteArray data = socket->readAll();
            qDebug() << "Received from server:" << data;
        });

        connect(socket, &QTcpSocket::connected, this, []() {
            qDebug() << "Connected to server!";
        });

        connect(socket, &QTcpSocket::disconnected, this, []() {
            qDebug() << "Disconnected from server!";
        });
    }

    void connectToServer(const QString& host, quint16 port) {
        socket->connectToHost(host, port);
    }

    void sendData(const QString& data) {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(data.toUtf8());
        } else {
            qDebug() << "Not connected to server!";
        }
    }

private:
    QTcpSocket* socket;
};

#endif // GAMECLIENT_H
