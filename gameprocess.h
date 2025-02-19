#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QDebug>
#include <QObject>

#include <servermanager.h>

class ServerManager;
class GameProcess : public QObject
{
    Q_OBJECT
public:
    GameProcess(ServerManager* serverManager);

signals:
    void stoneChoosing();
    void scissorsChoosing();
    void paperChoosing();
    void resultReady(QString resultMessage);

public slots:
    void setServerChoice(int choice);
    void setClientChoice(int choice);

private:
    enum Outcomes{
        server_win = 2,
        draw = 1,
        client_win = 0,
    };

    enum Choices{
        none = -1,
        stone = 0,
        scissors = 1,
        paper = 2,
    };

    void game();

    int serverPlayerChoice = none;
    int clientPlayerChoice = none;
};

#endif // GAMEPROCESS_H
