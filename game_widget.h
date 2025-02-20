#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

#include "aplicationmanager.h"
#include "gameprocess.h"

class AplicationManager;

//класс виджета игры
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(AplicationManager* sr,QWidget *parent = nullptr);
    ~GameWidget();

public slots:
    void clientDisconnectMessage();
    void serverDisconnectMessage();
    void waitEnemyMessage();
    void enemyWaitingMessage(int choice);

    void baseStateReturn();

    void setResult(int result);

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

    QLabel* youWin = nullptr;
    QLabel* youLose = nullptr;
    QLabel* draw = nullptr;

    QStackedWidget* resultWidget = nullptr;

    bool reslutOk = false;//если результат пришел
};

#endif // GAME_WIDGET_H
