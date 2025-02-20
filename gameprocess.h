#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QDebug>
#include <QObject>

#include <servermanager.h>

class ServerManager;

//класс обработчка игрового процесса
class GameProcess : public QObject
{
    Q_OBJECT
public:
    GameProcess(ServerManager* serverManager);

signals:
    void stoneChoosing();//оповезение о выборе каменя
    void scissorsChoosing();//оповещение о выборе ножниц
    void paperChoosing();//оповещение о выборе бумаги
    void resultReady(QString resultMessage);//оповещение о том, что резултат игры готов

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


    /*первый выиграл если*/
    void game();

    int serverPlayerChoice = none;
    int clientPlayerChoice = none;
};

#endif // GAMEPROCESS_H
