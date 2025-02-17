#include "servermanager.h"

#include <QTimer>
#include <QDebug>
#include <Qthread>

ServerManager::ServerManager()
{

}

ServerManager::~ServerManager()
{
    closeServer();
    closeConnection();
}


void ServerManager::createServer()
{
    if(!server)
    {
        server = new Server;
        connect(server, Server::serverIsReady, this, ServerManager::connectionIsOk);
        connect(server, Server::clientDisconnect, this,  ServerManager::clientDisconnectFromServer);
        connect(server, Server::clientChoiceIsAccepted, this, ServerManager::clientChoiceIsAccepted);
        server->startServer(1234);
    }
}

void ServerManager::closeServer()
{
    if(server)
    {
        disconnect(server, Server::serverIsReady, this, ServerManager::connectionIsOk);
        server->close();

        delete server;
        server = nullptr;
    }
}

void ServerManager::createConnection()
{
    if(!client)
    {
        client = new Client;
        connect(client, Client::clientIsReady, this, ServerManager::connectionIsOk);
        connect(client, Client::serverCloseForClient, this,  ServerManager::serverCloseForClient);
        connect(client, Client::serverChoiceIsAccepted, this, ServerManager::serverChoiceIsAccepted);
        connect(client, Client::serverSendResult, this, ServerManager::resultIsAccepted);

        client->connectToServer("127.0.0.1", 1234);
    }
}

void ServerManager::closeConnection()
{
    if(client)
    {
        disconnect(client, Client::clientIsReady, this, ServerManager::connectionIsOk);
        client->disconnectFromServer();

        delete client;
        client = nullptr;
    }
}


void ServerManager::sendMessage(QString message)
{
//    qDebug() << choice;

    if(client)
    {
        client->sendMessage(message);
    }

    if(server)
    {


        qDebug() << "server manager send message1: " << message;
        if(message.startsWith("game:"))
        {
            int serverChoice = message.mid(5).toInt();
            emit localChoiceIsAccepted(serverChoice);

        }

        if(message.startsWith("result:"))
        {
            int result = message.mid(7).toInt();

            emit resultIsAccepted(result);
//                       QThread::msleep(50); // Задержка 10 мс (можно увеличить)

        }



        qDebug() << "server manager send message2: " << message;
        server->sendMessageToClient(message);

    }



}


