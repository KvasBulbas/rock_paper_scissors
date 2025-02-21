    #include "gameprocess.h"

GameProcess::GameProcess(ServerManager* serverManager)
{
    //при выборе соответвущего действия игрока, отпрввляем его ввиде сообщения через serverManager
    connect(this, &GameProcess::stoneChoosing, serverManager, [serverManager](){
        serverManager->sendMessage("game:0");
    });

    connect(this, &GameProcess::scissorsChoosing, serverManager, [serverManager](){
        serverManager->sendMessage("game:1");
    });

    connect(this, &GameProcess::paperChoosing, serverManager, [serverManager](){
        serverManager->sendMessage("game:2");
    });


    //когда результат готов, отарвляем его ввиде ссообщения чеоез servermanager
    connect(this, &GameProcess::resultReady, serverManager, &ServerManager::sendMessage);

    //вызываем методы смены выобора сервера и клиента, когда приходит оповещение с их выбором
    connect(serverManager, &ServerManager::localChoiceIsAccepted, this, &GameProcess::setServerChoice);
    connect(serverManager, &ServerManager::clientChoiceIsAccepted, this, &GameProcess::setClientChoice);
}


void GameProcess::setServerChoice(int choice)//смена выбора сервера
{
    if(0 <= choice && choice <= 2)//если выбор пришел корректно
    {
        serverPlayerChoice = choice;
        game();//вывзываем метод обработки игрового процесса
    }
}

void GameProcess::setClientChoice(int choice)//смена выобра клиента
{
    if(0 <= choice && choice <= 2)//при выбор пришел корректно
    {
        clientPlayerChoice = choice;
        game();//вывзываем метод обработки игрового процесса
    }
}

void GameProcess::game()
{
    int result = 0;//обнуляем результат прошлой партии

    //если игроки сделали выбор
    if(serverPlayerChoice != none && clientPlayerChoice != none )
    {
        if(serverPlayerChoice == clientPlayerChoice)//если выборы одинаковые, то ничья
        {
            result = draw;
        }
        else
        {
            //перечисляем все случае выигрыша сервера
            if((serverPlayerChoice == stone && clientPlayerChoice == scissors) ||
               (serverPlayerChoice == scissors && clientPlayerChoice == paper) ||
               (serverPlayerChoice == paper && clientPlayerChoice == stone))
            {
                result = server_win;
            }
            else//иначе выиграл клиент
            {
                result = client_win;
            }
        }

        //обнуляем выборы игроков для следующей партии
        serverPlayerChoice = none;
        clientPlayerChoice = none;

        emit resultReady(QString("result:") + QString::number(result));//отправляем сигналом резултат ввиде сообщения
    }
}

