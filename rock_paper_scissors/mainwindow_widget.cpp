#include "mainwindow_widget.h"

#include <QDebug>

MainWindowWidget::MainWindowWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(450, 250);

    aplicationManager = new AplicationManager(this);
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    aplicationManager->exitToMenu();//задаем изначальное окно ввиде окна главного меню
}

MainWindowWidget::~MainWindowWidget()
{
    delete aplicationManager;
    if(subwidget)
        delete subwidget;
}

void MainWindowWidget::setWidget(QWidget* newSubWidget)//метод смены виджета
{
    if(subwidget)//виджет удаляется из layout, а также освобождается память из под указателя на этот виджет
    {
        layout->removeWidget(subwidget);
        delete subwidget;
    }

    //присвоение указателю адреса нового виджета, а также помощение его в layot
    subwidget = newSubWidget;
    layout->addWidget(subwidget);
}






