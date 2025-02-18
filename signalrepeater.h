#ifndef SIGNALREPEATER_H
#define SIGNALREPEATER_H

#include "mainwindow_widget.h"
#include "servermanager.h"
#include "mainmenu_widget.h"
#include "game_widget.h"
#include "localhost_widget.h"

#include <QObject>

class MainWindowWidget;

/*Класс aplication manager осуществеляет управление всем приложением. С помощью него происходит взаимодействие
между виджетам, а также он хранит объяект ServerManager, который осуществляет управление сетевой составляющей
приложения. В случае необходимости этот класс может предоствить указателель на ServerManager*/
class AplicationManager : public QObject
{
    Q_OBJECT
public:
    AplicationManager(MainWindowWidget* mainwindow);
    ~AplicationManager();

public slots:
    void gameStart();

    void exitToMenu();

    void aplicationClose();

    void openLocalhostMenu();

    ServerManager* getServerManager();

private:
    MainWindowWidget* mainwindow = nullptr;

    ServerManager* serverManager = nullptr;
};

#endif // SIGNALREPEATER_H
