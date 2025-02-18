#ifndef MAINWINDOW_WIDGET_H
#define MAINWINDOW_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>

#include "signalrepeater.h"

class AplicationManager;

//Класс главного окна. Является главным виджетом, через который запускается приложение, а также отображает остальные
//виджеты, смена которых происходит с помощью класса Aplication manager

class MainWindowWidget : public QWidget
{
    Q_OBJECT

public:
    MainWindowWidget(QWidget *parent = nullptr);
    ~MainWindowWidget();

public slots:
    void setWidget(QWidget* newSubWidget);

private:
    AplicationManager* aplicationManager = nullptr;

    QVBoxLayout* layout = nullptr;

    QWidget* subwidget = nullptr;
};
#endif // MAINWINDOW_WIDGET_H
