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
        connect(client, Client::serverSendResult, this, ServerManager::resultIsAccepted);
        connect(client, Client::serverChoiceIsAccepted, this, ServerManager::serverChoiceIsAccepted);
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

        if(message.startsWith("game:"))
        {
            int serverChoice = message.mid(5).toInt();
            emit localChoiceIsAccepted(serverChoice);
        }

        if(message.startsWith("result:"))
        {
            int result = message.mid(7).toInt();
//            qDebug() << "send message: result" << message;
            emit resultIsAccepted(result);
        }

        server->sendMessageToClient(message);
    }



}


