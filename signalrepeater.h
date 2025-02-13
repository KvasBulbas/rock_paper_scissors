#ifndef SIGNALREPEATER_H
#define SIGNALREPEATER_H

#include "mainwindow_widget.h"
#include "servermanager.h"
#include "mainmenu_widget.h"
#include "game_widget.h"
#include "localhost_widget.h"

#include <QObject>

//class ServerManager;
//class MainMenuWidget;
//class GameWidget;
//class LocalHostWidget;

class MainWindowWidget;

class SignalRepeater : public QObject
{
    Q_OBJECT
public:
    SignalRepeater(MainWindowWidget* mainwindow);
    ~SignalRepeater();

signals:

public slots:
    void gameStart();

    void exitToMenu() const;

    void aplicationClose() const;

    void openLocalhostMenu();

    ServerManager* getServerManager();

//    void setServerManager(const ServerManager* sm);

private:
    MainWindowWidget* mainwindow = nullptr;

    ServerManager* serverManager = nullptr;





};

#endif // SIGNALREPEATER_H
