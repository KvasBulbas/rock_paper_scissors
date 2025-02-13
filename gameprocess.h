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


private:
    enum Outcomes{
        win_first = 1,
        win_second = -1,
        draw = 0,
    };

    enum Choices{
        none = -1,
        stone = 0,
        scissors = 1,
        paper = 2,
    };

    void game();

    int firstPlayerChoice = none;
    int secondPlayerChoice = none;

public slots:
    void setFirstPlayerChoice(int choice);
    void setSecondPlayerChoice(int choice);

};

#endif // GAMEPROCESS_H
