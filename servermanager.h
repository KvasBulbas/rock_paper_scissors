#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "gameserver.h"
#include "gameclient.h"
#include <QObject>

//class Client;
class ServerManager : public QObject
{
    Q_OBJECT
public:
    ServerManager();
    ~ServerManager();


public slots:
    void createServer();
    void closeServer();

    void createConnection(const QString &host, quint16 port);
    void closeConnection();
    void sendMessage(QString message);
//    void sendResult(QString result);



signals:
    void connectionIsOk();
    void clientDisconnectFromServer();
    void serverCloseForClient();
    void clientChoiceIsAccepted(int clientChoice);
    void serverChoiceIsAccepted(int serverChoice);
    void localChoiceIsAccepted(int localChoice);
    void resultIsAccepted(int result);
    void serverCreated(const QString& serverAdresses, const QString& portAdress);

private:
    Server* server = nullptr;
    Client* client = nullptr;

    bool isClient = false;

};

#endif // SERVERMANAGER_H
