#include "signalrepeater.h"
#include <QDebug>

//#include <mainmenu_widget.h>
SignalRepeater::SignalRepeater(MainWindowWidget *mainwindow):mainwindow(mainwindow){}

void SignalRepeater::gameStart()
{
    qDebug() << "start game";
    mainwindow->setWidget(1);
}

void SignalRepeater::exitToMenu()
{
    qDebug() << "exit to menu";
    mainwindow->setWidget(0);
}

void SignalRepeater::aplicationClose()
{
    qDebug() << "aplication close";
    mainwindow->close();
}

