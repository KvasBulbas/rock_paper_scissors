#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QDebug>

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include "signalrepeater.h"
#include "gameprocess.h"

class SignalRepeater;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(SignalRepeater* sr,QWidget *parent = nullptr);
    ~GameWidget();

public slots:
    void clientDisconnectMessage();
    void serverDisconnectMessage();
    void waitEnemyMessage();
    void enemyWaitingMessage();

    void baseStateReturn();

private:
    QPushButton* exitToMenuButton = nullptr;

    QPushButton* rockButton = nullptr;
    QPushButton* scissorsButton = nullptr;
    QPushButton* paperButton = nullptr;

    QLabel* firstPlayerReady = nullptr;
    QLabel* secondPlayerReady = nullptr;

    QLabel* clientDisconnect = nullptr;
    QLabel* serverDiconnect= nullptr;

    ServerManager* serverManager = nullptr;

    GameProcess* gameProcess = nullptr;

};

#endif // GAME_WIDGET_H
