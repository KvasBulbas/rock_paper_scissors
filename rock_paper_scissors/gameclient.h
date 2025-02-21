#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QTcpSocket>

//класс клиента, который подключается к серверу
class Client : public QTcpSocket {
    Q_OBJECT

public:
    Client();

    void connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    void sendMessage(const QString &message);

signals:
    void clientIsReady();//клиент подключился к серверу и готов к игре
    void serverCloseForClient();//сервер, к которому был подлкючен клиент, закрылся
    void serverChoiceIsAccepted(int clientChoice);//сервер сделал выбор и отправил его клиенту
    void serverSendResult(int result);//сервер отправил резултат игры клиенту

private slots:
    void onConnected();

    void onReadyRead();

    void onDisconnected();

};

#endif // GAMECLIENT_H
