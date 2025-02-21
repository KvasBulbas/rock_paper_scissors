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


void ServerManager::createServer()//метод создания объекта сервера, а также подключения к нему коннектов
{
    if(!server && !client)
    {
        server = new Server;
        //если к нашему серверу подключился клмент, то срабатывает сигнал данного класса, предназанченный для дальнейшего оповещения об этом событии
        connect(server, &Server::serverIsReady, this, &ServerManager::connectionIsOk);
        //если клинет отлючился от сервера, то срабатывает сигнал данного класса, предназанченный для дальнейшего оповещения об этом событии
        connect(server, &Server::clientDisconnect, this,  &ServerManager::clientDisconnectFromServer);
        //если клиент сделал выбор и отправил его нашему серверу, то срабатывает сигнал данного класса, предназанченный для дальнейшего оповещения об этом событии
        connect(server, &Server::clientChoiceIsAccepted, this, &ServerManager::clientChoiceIsAccepted);
        //сервер был создан, то срабатывает сигнал данного класса, предназанченный для дальнейшего оповещения об этом событии
        connect(server, &Server::serverCreated, this, &ServerManager::serverCreated);
        server->startServer(1234);//метод старта сервера
    }
}

void ServerManager::closeServer()//метод удаления сервра, он закрывает сервер, отключает все конекты и удаляет объект
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
    if(!client &&  !server)
    {
        client = new Client;
        //если к серверу подключился наш клмент, то срабатывает сигнал данного класса, предназанченный для дальнейшего оповещения об этом событии
        connect(client, &Client::clientIsReady, this, &ServerManager::connectionIsOk);
        //если сервер, к которому был подключен наш клмент был закрыт, то срабатывает сигнал данного класса, предназанченный для дальнейшего оповещения об этом событии
        connect(client, &Client::serverCloseForClient, this,  &ServerManager::serverCloseForClient);
        //если сервер сделал выбор и отправил его нашему клиенту, то срабатывает сигнал данного класса, предназанченный для дальнейшего оповещения об этом событии
        connect(client, &Client::serverChoiceIsAccepted, this, &ServerManager::serverChoiceIsAccepted);
        //если сервер отправил результат нашему клиенту, то срабатывает сигнал данного класса, предназанченный для дальнейшего оповещения об этом событии
        connect(client, &Client::serverSendResult, this, &ServerManager::resultIsAccepted);

        client->connectToServer(host, port);//вызываем метод подключения клиента к серверу
    }
}

void ServerManager::closeConnection()//метод отлючает клмента от сервера, а также отключает все коннекты свзяанные с клмнтом и удаляет объект клиента
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

//через этот метод происходит отправка сообщений клиентом или сервером, а такжек валидация данных для сообщений которые пришли локально для сервера
void ServerManager::sendMessage(QString message)
{
    if(client)
        client->sendMessage(message);//клмент отправляет сообщение

    if(server)
    {
        if(message.startsWith("game:"))//если сообщение о выборе хода
        {
            int serverChoice = message.mid(5).toInt();//достаем ход
            emit localChoiceIsAccepted(serverChoice);//если ход был сделан локально, то оповещаем, передавая ход

        }

        if(message.startsWith("result:"))//если пришел результат, то делам тоже самое то, что и ходом
        {
            int result = message.mid(7).toInt();
            emit resultIsAccepted(result);

        }
        server->sendMessageToClient(message);//отправляем клиенту сообщение
    }
}


