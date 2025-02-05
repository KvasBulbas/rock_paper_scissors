#ifndef SIGNALREPEATER_H
#define SIGNALREPEATER_H

#include "mainwindow_widget.h"

#include <QObject>

class MainWindowWidget;

class SignalRepeater : public QObject
{
    Q_OBJECT
public:
    SignalRepeater(MainWindowWidget* mainwindow);
//    SignalRepeater(){}

signals:

public slots:
    void gameStart();

    void exitToMenu();

    void aplicationClose();

    void openLocalhostMenu();

private:
    MainWindowWidget* mainwindow = nullptr;

};

#endif // SIGNALREPEATER_H
