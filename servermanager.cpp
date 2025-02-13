#include "servermanager.h"

#include <QTimer>
#include <QDebug>

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


void ServerManager::sendChoice(int choice)
{
//    qDebug() << choice;
    if(client)
    {
        QString message = QString("game:").arg(choice);
        qDebug() << message;
        client->sendMessage(message);
//        QTimer::singleShot(2000, [this]() {
//            client->sendMessage("");
//        });
    }

    if(server)
    {

        emit serverChoiceIsAccepted(choice);
    }
}

