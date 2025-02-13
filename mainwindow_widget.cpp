#include "mainwindow_widget.h"

#include <QDebug>

MainWindowWidget::MainWindowWidget(QWidget *parent)
    : QWidget(parent)
{
    sr = new SignalRepeater(this);
    layout = new QVBoxLayout(this);

    sr->exitToMenu();
}

MainWindowWidget::~MainWindowWidget()
{
    delete sr;
    if(subwidget)
        delete subwidget;
}

void MainWindowWidget::setWidget(QWidget* newSubWidget)
{
//    qDebug() << "setWidget";

    if(subwidget)
    {
        layout->removeWidget(subwidget);
        delete subwidget;
        qDebug() << "deleteWidget";
    }

    subwidget = newSubWidget;
    layout->addWidget(subwidget);
}






