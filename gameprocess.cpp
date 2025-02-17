    #include "gameprocess.h"

GameProcess::GameProcess(ServerManager* serverManager)
{
    connect(this, GameProcess::stoneChoosing, serverManager, [serverManager](){
        serverManager->sendMessage("game:0");
    });

    connect(this, GameProcess::scissorsChoosing, serverManager, [serverManager](){
        serverManager->sendMessage("game:1");
    });

    connect(this, GameProcess::paperChoosing, serverManager, [serverManager](){
        serverManager->sendMessage("game:2");
    });


    connect(this, GameProcess::resultReady, serverManager, ServerManager::sendMessage);
    connect(serverManager, ServerManager::localChoiceIsAccepted, this, setServerChoice);
    connect(serverManager, ServerManager::clientChoiceIsAccepted, this, setClientChoice);





}


void GameProcess::setServerChoice(int choice)
{
//    qDebug() << "server player choice" << choice;
    if(0 <= choice && choice <= 2)
    {
        serverPlayerChoice = choice;
        game();
    }
}

void GameProcess::setClientChoice(int choice)
{
//    qDebug() << "client player choice" << choice;
    if(0 <= choice && choice <= 2)
    {
        clientPlayerChoice = choice;
        game();
    }
}

void GameProcess::game()
{

    int result = 0;

    if(serverPlayerChoice != none && clientPlayerChoice != none )
    {
//        qDebug() << serverPlayerChoice;
//        qDebug() << clientPlayerChoice;

        if(serverPlayerChoice == stone && clientPlayerChoice == scissors )
        {
            result = server_win;
//            qDebug() <<  "server win";
        }


        if(serverPlayerChoice == stone && clientPlayerChoice == paper )
        {
            result = client_win;
//            qDebug() <<  "client win";
        }


        if(serverPlayerChoice == stone && clientPlayerChoice == stone )
        {
            result = draw;
//            qDebug() <<  "draw";

        }

        if(serverPlayerChoice == scissors && clientPlayerChoice == scissors )
        {
            result = draw;
//            qDebug() <<  "draw";
        }


        if(serverPlayerChoice == scissors && clientPlayerChoice == stone )
        {
            result = client_win;
//            qDebug() <<  "client win";
        }


        if(serverPlayerChoice == scissors && clientPlayerChoice == paper )
        {
            result = server_win;
//            qDebug() <<  "server win";
        }


        if(serverPlayerChoice == paper && clientPlayerChoice == paper )
        {
            result = draw;
//            qDebug() <<  "draw";
        }


        if(serverPlayerChoice == paper && clientPlayerChoice == stone )
        {
            result = server_win;
//            qDebug() <<  "server win";
        }

        if(serverPlayerChoice == paper && clientPlayerChoice == scissors )
        {
            result = client_win;
//            qDebug() <<  "client win";
        }


        serverPlayerChoice = none;
        clientPlayerChoice = none;

//        qDebug() << "game result: " << result;


        emit resultReady(QString("result:") + QString::number(result));

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
