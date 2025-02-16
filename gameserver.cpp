#include "gameserver.h"

Server::Server(QObject *parent) : QTcpServer(parent)
    {
        connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);
    }

void Server::startServer(quint16 port) {
    if (listen(QHostAddress::Any, port))
    {
        qDebug() << "Start server" << port;
    }
    else
    {
        qDebug() << "Start server: error" << errorString();
    }
}

void Server::sendMessageToClient(const QString &message)
{
    if (clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState)
        clientSocket->write(message.toUtf8());

}



void Server::onNewConnection() {
    clientSocket = nextPendingConnection();
    //        clients.push_back(clientSocket);
    qDebug() << "New connection:" << clientSocket->peerAddress().toString();

    connect(clientSocket, &QTcpSocket::readyRead, [this]()
            {
                QByteArray data = clientSocket->readAll();
//                qDebug() << data;
                if(data.startsWith("game:"))
                {
                    int clientChoice = data.mid(5).toInt();
                    emit clientChoiceIsAccepted(clientChoice);
                }
            }
            );

    connect(clientSocket, &QTcpSocket::disconnected, [this]()
            {
                qDebug() << "Client disconnect:"; /*<< clientSocket->peerAddress().toString();
                                                               clientSocket->deleteLater();*/
                emit clientDisconnect();
            }
            );

    emit serverIsReady();
}
