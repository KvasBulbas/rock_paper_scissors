#ifndef LOCALHOSTWIDGET_H
#define LOCALHOSTWIDGET_H

#include "aplicationmanager.h"
//#include "gameclient.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTcpSocket>
#include <QKeyEvent>
#include <QLineEdit>
#include <QTextEdit>


class AplicationManager;

class AdressLineEdit : public QWidget
{
    Q_OBJECT
public:
    AdressLineEdit(AplicationManager *aplicationManager, QWidget *parent = nullptr);

public slots:
    void enterServerName();

private:
    QLineEdit* hostLineEdit = nullptr;
    QLineEdit* portLineEdit = nullptr;
    QLabel* colon = nullptr;

    ServerManager* serverManager = nullptr;
};



class LocalHostWidget : public QWidget
{
    Q_OBJECT
public:
    LocalHostWidget(AplicationManager *aplicationManager, QWidget *parent = nullptr);
    ~LocalHostWidget();

signals:
    void escPressed();

public slots:
    void createLobby();
    void baseStateReturn();
    void clientConnect();
    void showCreatedMessage(const QString& serverAdresses, const QString& port);

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Escape)
            emit escPressed();
    }

private:
    QPushButton* createLobbyButton = nullptr;
    QPushButton* findLobbyButton = nullptr;
    QPushButton* connectButton = nullptr;
    QPushButton* exitToMenuButton = nullptr;

    QTextEdit* createLobbyMesage = nullptr;
    QLabel* connectionMesage = nullptr;

    AdressLineEdit* adressLineEdit = nullptr;

    ServerManager* serverManager = nullptr;

};

#endif // LOCALHOSTWIDGET_H
