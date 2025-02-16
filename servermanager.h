#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "gameserver.h"
#include <QObject>

class ServerManager : public QObject
{
    Q_OBJECT
public:
    ServerManager();
    ~ServerManager();


public slots:
    void createServer();
    void closeServer();

    void createConnection();
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

private:
    Server* server = nullptr;
    Client* client = nullptr;

    bool isClient = false;

};

#endif // SERVERMANAGER_H
