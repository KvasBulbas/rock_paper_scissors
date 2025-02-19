#include "gameserver.h"
#include <QCoreApplication>
#include <QNetworkInterface>

Server::Server(QObject *parent) : QTcpServer(parent)
{
    connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

void Server::startServer(quint16 port)
{
    if (listen(QHostAddress::Any, port))
    {
        QString stringPort = QString::number(this->serverPort());

        QList<QHostAddress> ipAddresses;
        const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

        for (const QNetworkInterface &interface : interfaces)
        {
            if (!(interface.flags() & QNetworkInterface::IsUp) ||
                !(interface.flags() & QNetworkInterface::IsRunning)) {
                continue;
            }

            const QList<QNetworkAddressEntry> entries = interface.addressEntries();
            for (const QNetworkAddressEntry &entry : entries) {
                QHostAddress ip = entry.ip();

                if (ip.protocol() == QAbstractSocket::IPv4Protocol &&
                    ip != QHostAddress::LocalHost) {
                    ipAddresses.append(ip);
                }
            }
        }

        QString stringAdresses;
        for(const QHostAddress &address : ipAddresses)
            stringAdresses +=  address.toString() + ", ";

        emit serverCreated(stringAdresses,stringPort);
    }
    else
    {
        qDebug() << "Start server: error" << errorString();
    }
}

void Server::sendMessageToClient(const QString &message)
{
    if (clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        clientSocket->write(message.toUtf8());
        clientSocket->flush();
        QCoreApplication::processEvents();
    }
}



void Server::onNewConnection()
{
    clientSocket = nextPendingConnection();
    qDebug() << "New connection:" << clientSocket->peerAddress().toString();

    connect(clientSocket, &QTcpSocket::readyRead, [this]()
            {
                QByteArray data = clientSocket->readAll();
                if(data.startsWith("game:"))
                {
                    int clientChoice = data.mid(5).toInt();
                    emit clientChoiceIsAccepted(clientChoice);
                }
            }
            );

    connect(clientSocket, &QTcpSocket::disconnected, [this]()
            {
                qDebug() << "Client disconnect:";
                emit clientDisconnect();
            }
            );

    emit serverIsReady();
}
