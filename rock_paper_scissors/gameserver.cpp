#include "gameserver.h"
#include <QCoreApplication>
#include <QNetworkInterface>

Server::Server(QObject *parent) : QTcpServer(parent)
{
    connect(this, &QTcpServer::newConnection, this, &Server::onNewConnection);//если клмент подклбчился к серверу
}

void Server::startServer(quint16 port)
{
    if (this->listen(QHostAddress::Any, port))//открываем сервер
    {
        QString stringPort = QString::number(this->serverPort());//возваращаем порт

        QList<QHostAddress> ipAddresses;//список адресов ipv4, по которым можно подлючиться к серверу
        const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();//cписок всех сетевых интерфейсо

        for (const QNetworkInterface &interface : interfaces)
        {
            //если порт активен и работает
            if (!(interface.flags() & QNetworkInterface::IsUp) || !(interface.flags() & QNetworkInterface::IsRunning))
                continue;

            const QList<QNetworkAddressEntry> entries = interface.addressEntries();//получаем ip адреса для каждого интерфейса
            for (const QNetworkAddressEntry &entry : entries)
            {
                QHostAddress ip = entry.ip();

                //если адрес ipv4 и он не локалхост, то добавляем его в список
                if (ip.protocol() == QAbstractSocket::IPv4Protocol && ip != QHostAddress::LocalHost)
                    ipAddresses.append(ip);

            }
        }

        //формируем строку из найденных ip адресов
        QString stringAdresses;
        for(const QHostAddress &address : ipAddresses)
            stringAdresses +=  address.toString() + ", ";

        emit serverCreated(stringAdresses,stringPort);//отправляем сигнал о том, что сервер был создан вместе с адресами, к которым можно подлючиться
    }
    else
    {
        qDebug() << "Start server: error" << errorString();
    }
}

void Server::sendMessageToClient(const QString &message)//метод отправки клменту сообщения
{
    if (clientSocket && clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        clientSocket->write(message.toUtf8());//отправлем клиенту сообщение

        //следуюшие методы нужны для того, чтобы сообщения отправлялись моментально
        clientSocket->flush();
        QCoreApplication::processEvents();
    }
}

void Server::onNewConnection()
{
    clientSocket = this->nextPendingConnection();//получаем клиента, который подключился к серверу
    qDebug() << "New connection:" << clientSocket->peerAddress().toString();

    //при отправке сообщения клментом
    connect(clientSocket, &QTcpSocket::readyRead, [this]()
            {
                QByteArray data = clientSocket->readAll();
                if(data.startsWith("game:"))
                {
                    int clientChoice = data.mid(5).toInt();
                    emit clientChoiceIsAccepted(clientChoice);//вызываем сигнал сообщающий то, что клмент сделал выбор
                }
            }
            );

    //при отлючении клиента
    connect(clientSocket, &QTcpSocket::disconnected, [this]()
            {
                qDebug() << "Client disconnect:";
                emit clientDisconnect();//сообщаем, что клиент отключился
            }
            );

    emit serverIsReady();//сообщаем, что к серверу подключен клинент
}
