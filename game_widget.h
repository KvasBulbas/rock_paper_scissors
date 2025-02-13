#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QDebug>

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include "signalrepeater.h"

class SignalRepeater;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(SignalRepeater* sr,QWidget *parent = nullptr);
    ~GameWidget();

public slots:
    void showMessage();

private:
    QPushButton* exitToMenuButton = nullptr;

    QPushButton* rockButton = nullptr;
    QPushButton* scissorsButton = nullptr;
    QPushButton* paperButton = nullptr;

    QLabel* firstPlayerReady = nullptr;
    QLabel* secondPlayerReady = nullptr;

    ServerManager* serverManager = nullptr;

};

#endif // GAME_WIDGET_H
