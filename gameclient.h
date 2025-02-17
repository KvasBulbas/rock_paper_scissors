#ifndef GAMECLIENT_H
#define GAMECLIENT_H


#include <QTcpSocket>
#include <QDebug>

class Client : public QObject {
    Q_OBJECT

public:
    Client(QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);

    void disconnectFromServer();

    void sendMessage(const QString &message);

    bool checkConnection();


signals:
    void clientIsReady();
    void serverCloseForClient();
    void serverChoiceIsAccepted(int clientChoice);
    void serverSendResult(int result);

private slots:
    void onConnected();

    void onReadyRead();

    void onDisconnected();

private:
    QTcpSocket socket;
};

#endif // GAMECLIENT_H
