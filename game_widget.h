#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QDebug>

#include <QWidget>
#include <QPushButton>

#include "signalrepeater.h"

class SignalRepeater;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(const SignalRepeater* sr,QWidget *parent = nullptr);
    ~GameWidget();

private:
    QPushButton* exitToMenuButton = nullptr;

    QPushButton* rockButton = nullptr;
    QPushButton* scissorsButton = nullptr;
    QPushButton* paperButton = nullptr;

};

#endif // GAME_WIDGET_H
