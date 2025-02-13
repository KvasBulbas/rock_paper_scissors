#include "mainwindow_widget.h"
#include "gameserver.h"
//#include "gameclient.h"

#include <Qtimer>
#include <QApplication>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowWidget w;
    w.show();




    return a.exec();
}
