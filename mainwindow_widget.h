#ifndef MAINWINDOW_WIDGET_H
#define MAINWINDOW_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "signalrepeater.h"
//#include "mainmenu_widget.h"
//#include "game_widget.h"
//#include "localhost_widget.h"

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
    void setWidget(QWidget* newSubWidget);

private:
    SignalRepeater* sr = nullptr;

    QVBoxLayout* layout = nullptr;

//    MainMenuWidget* mainMenu = nullptr;
//    GameWidget* game = nullptr;
//    LocalHostWidget* localHostMenu = nullptr;

//    QStackedWidget* stackedWidget = nullptr;

    QWidget* subwidget = nullptr;


};
#endif // MAINWINDOW_WIDGET_H
