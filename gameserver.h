#ifndef GAMESERVER_H
#define GAMESERVER_H

//#include "signalrepeater.h"

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>


// Сервер
class Server : public QTcpServer {
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);

    void startServer(quint16 port) ;
    void sendMessageToClient(const QString &message);

signals:
    void serverCreated(const QString &adressesMessage, const QString &portMessage);
    void clientDisconnect();
    void serverIsReady();
    void clientChoiceIsAccepted(int clientChoice);

private slots:
    void onNewConnection();

private:
    QTcpSocket* clientSocket = nullptr;

};

#endif // GAMESERVER_H
