#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QDebug>

class GameProcess
{
private:

    enum Outcomes{
        win_first = 1,
        win_second = -1,
        draw = 0,
    };

public:
    GameProcess();

    void game(int firstPlayerChoice, int secondPlayerChoice)
    {
        switch (firstPlayerChoice - secondPlayerChoice) {
        case win_first:
            qDebug() << "first won";
            break;
        case win_second:
            qDebug() << "second won";
            break;
        case draw:
            qDebug() << "draw";
        }
    }

private:


};

#endif // GAMEPROCESS_H
