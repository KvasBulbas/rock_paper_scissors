#include "gameprocess.h"

GameProcess::GameProcess(ServerManager* serverManager)
{
    connect(this, GameProcess::stoneChoosing, serverManager, [serverManager](){
        serverManager->sendChoice(0);
    });

    connect(this, GameProcess::scissorsChoosing, serverManager, [serverManager](){
        serverManager->sendChoice(1);
    });

    connect(this, GameProcess::paperChoosing, serverManager, [serverManager](){
        serverManager->sendChoice(2);
    });

    connect(serverManager, ServerManager::serverChoiceIsAccepted, this, setFirstPlayerChoice);
    connect(serverManager, ServerManager::clientChoiceIsAccepted, this, setSecondPlayerChoice);
}


void GameProcess::setFirstPlayerChoice(int choice)
{
    if(0 <= choice && choice <= 2)
    {
        firstPlayerChoice = choice;
        game();
    }
}

void GameProcess::setSecondPlayerChoice(int choice)
{
    if(0 <= choice && choice <= 2)
    {
        secondPlayerChoice = choice;
        game();
    }
}

void GameProcess::game()
{


    if(firstPlayerChoice != none && secondPlayerChoice != none )
    {
        qDebug() << firstPlayerChoice;
        qDebug() << secondPlayerChoice;

        if(firstPlayerChoice == stone && secondPlayerChoice == scissors )
            qDebug() <<  "server win";

        if(firstPlayerChoice == stone && secondPlayerChoice == paper )
            qDebug() <<  "client win";

        if(firstPlayerChoice == stone && secondPlayerChoice == stone )
            qDebug() <<  "draw";

        if(firstPlayerChoice == scissors && secondPlayerChoice == scissors )
            qDebug() <<  "draw";

        if(firstPlayerChoice == scissors && secondPlayerChoice == stone )
            qDebug() <<  "client win";

        if(firstPlayerChoice == scissors && secondPlayerChoice == paper )
            qDebug() <<  "server win";

        if(firstPlayerChoice == paper && secondPlayerChoice == paper )
            qDebug() <<  "draw";

        if(firstPlayerChoice == paper && secondPlayerChoice == stone )
            qDebug() <<  "server win";

        if(firstPlayerChoice == paper && secondPlayerChoice == scissors )
            qDebug() <<  "client win";

        firstPlayerChoice = none;

        secondPlayerChoice = none;
    }



//        switch (firstPlayerChoice - secondPlayerChoice) {
//        case win_first:
//        qDebug() << "first won";
//        break;
//        case win_second:
//        qDebug() << "second won";
//        break;
//        case draw:
//        qDebug() << "draw";
//        }
}
//void GameProcess::stoneChoosing()
//{

//}

//void GameProcess::scissorsChoosing()
//{

//}

//void GameProcess::paperChoosing()
//{

//}
