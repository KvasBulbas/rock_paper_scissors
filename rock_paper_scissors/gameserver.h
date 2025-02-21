#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>

// Класс сервера
class Server : public QTcpServer {
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);

    void startServer(quint16 port) ;
    void sendMessageToClient(const QString &message);

signals:
    void serverCreated(const QString &adressesMessage, const QString &portMessage);//сервер был создан
    void clientDisconnect();//клиент откобчился
    void serverIsReady();//к серверу подключился клиент
    void clientChoiceIsAccepted(int clientChoice);//клиент сделал выбор и прислал его

private slots:
    void onNewConnection();

private:
    QTcpSocket* clientSocket = nullptr;

};

#endif // GAMESERVER_H
