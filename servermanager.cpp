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
        connect(server, Server::serverIsReady, this, connectionIsOk);
        server->startServer(1234);
    }
}

void ServerManager::closeServer()
{
    if(server)
    {
        disconnect(server, Server::serverIsReady, this, connectionIsOk);
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
        connect(client, Client::clientIsReady, this, connectionIsOk);
        client->connectToServer("127.0.0.1", 1234);
    }
}

void ServerManager::closeConnection()
{
    if(client)
    {
        disconnect(client, Client::clientIsReady, this, connectionIsOk);
        client->disconnectFromServer();

        delete client;
        client = nullptr;
    }
}


void ServerManager::sendChoice(int choice)
{
    if(isClient)
    {
        QString message = QString("game:").arg(choice);
        client->sendMessage(message);
//        QTimer::singleShot(2000, [this]() {
//            client->sendMessage("");
//        });
    }
    else
    {
        server->setServerChoice(choice);
    }
}

