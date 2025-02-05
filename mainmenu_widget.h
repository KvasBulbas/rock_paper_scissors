#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include "signalrepeater.h"

#include <QDebug>

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

class SignalRepeater;

class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    MainMenuWidget(const SignalRepeater* sr, QWidget *parent = nullptr);
    ~MainMenuWidget();

signals:
    void gameStart();

private:
    QStackedWidget* stackedWidget = nullptr;

    QPushButton* gameVsBotButton = nullptr;
    QPushButton* localGameButton = nullptr;

    QPushButton* aplicationCloseButton = nullptr;
};

#endif // MAINMENU_WIDGET_H
