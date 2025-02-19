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
        connect(server, &Server::serverIsReady, this, &ServerManager::connectionIsOk);
        connect(server, &Server::clientDisconnect, this,  &ServerManager::clientDisconnectFromServer);
        connect(server, &Server::clientChoiceIsAccepted, this, &ServerManager::clientChoiceIsAccepted);   
        connect(server, &Server::serverCreated, this, &ServerManager::serverCreated);
        server->startServer(1234);
    }
}

void ServerManager::closeServer()
{
    if(server)
    {
        disconnect(server, &Server::serverIsReady, this, &ServerManager::connectionIsOk);
        disconnect(server, &Server::clientDisconnect, this,  &ServerManager::clientDisconnectFromServer);
        disconnect(server, &Server::clientChoiceIsAccepted, this, &ServerManager::clientChoiceIsAccepted);
        server->close();

        delete server;
        server = nullptr;
    }
}

void ServerManager::createConnection(const QString &host, quint16 port)
{
    if(!client)
    {
        client = new Client;
        connect(client, &Client::clientIsReady, this, &ServerManager::connectionIsOk);
        connect(client, &Client::serverCloseForClient, this,  &ServerManager::serverCloseForClient);
        connect(client, &Client::serverChoiceIsAccepted, this, &ServerManager::serverChoiceIsAccepted);
        connect(client, &Client::serverSendResult, this, &ServerManager::resultIsAccepted);

        client->connectToServer(host, port);
    }
}

void ServerManager::closeConnection()
{
    if(client)
    {
        disconnect(client, &Client::clientIsReady, this, &ServerManager::connectionIsOk);
        disconnect(client, &Client::serverCloseForClient, this,  &ServerManager::serverCloseForClient);
        disconnect(client, &Client::serverChoiceIsAccepted, this, &ServerManager::serverChoiceIsAccepted);
        disconnect(client, &Client::serverSendResult, this, &ServerManager::resultIsAccepted);
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

        }



        qDebug() << "server manager send message2: " << message;
        server->sendMessageToClient(message);

    }



}


