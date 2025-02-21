#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "gameserver.h"
#include "gameclient.h"
#include <QObject>


/*класс который отвечает за сетевое подключение. Через него происходит взаимодействие с клаасами клиента и сервера.
В теории должен иметь проинцелезировааным только объект сервера или клиента. Также производит валидации сообщений для сервера пришедшие локально*/
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

signals:
    void connectionIsOk();//сигнал срабатывающий при подключении клтента к серверу
    void clientDisconnectFromServer();//срабатывает когда клмент отключается от сервера
    void serverCloseForClient();//сервер был закрыт, когда к нему был подклбчен клмент
    //климент из другого приложения отправил сообщение, которое пришло нашему серверу о том, что клиент сделал ход
    void clientChoiceIsAccepted(int clientChoice);
    //сервер из другого приложения отправил сообщение, которое пришло нашему клиенту о том, что сервер сделал ход
    void serverChoiceIsAccepted(int serverChoice);
    void localChoiceIsAccepted(int localChoice);//сервер который, запущен в данном приложении сделал ход
    void resultIsAccepted(int result);//сообщение о том, что пришел результат, локально или от другого сервера(в случае клиента)
    void serverCreated(const QString& serverAdresses, const QString& portAdress);//сервер был создан

private:
    Server* server = nullptr;
    Client* client = nullptr;
};

#endif // SERVERMANAGER_H
