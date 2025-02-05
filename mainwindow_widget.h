#ifndef MAINWINDOW_WIDGET_H
#define MAINWINDOW_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

#include "signalrepeater.h"
#include "mainmenu_widget.h"
#include "game_widget.h"
#include "localhost_widget.h"

class SignalRepeater;
class MainMenuWidget;
class GameWidget;
class LocalHostWidget;

class MainWindowWidget : public QWidget
{
    Q_OBJECT

public:
    MainWindowWidget(QWidget *parent = nullptr);
    ~MainWindowWidget();

public slots:
    void setWidget(const int index);

private:
    SignalRepeater* sr = nullptr;

    MainMenuWidget* mainMenu = nullptr;
    GameWidget* game = nullptr;
    LocalHostWidget* localHostMenu = nullptr;

    QStackedWidget* stackedWidget = nullptr;


};
#endif // MAINWINDOW_WIDGET_H
