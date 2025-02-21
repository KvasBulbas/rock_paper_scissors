#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include "aplicationmanager.h"

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QKeyEvent>

class AplicationManager;

/*Класс виджета главного меню. Предостваляет интрефейс главного меню с кнопками. Взаимодействуйет с остальным приложением
через AplicationManager. С помощью этого класса можно открыть меню подлкючения, или закрыть приложение.*/
class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    MainMenuWidget(const AplicationManager* sr, QWidget *parent = nullptr);
    ~MainMenuWidget();

private:
    QPushButton* gameButton = nullptr;
    QPushButton* aplicationCloseButton = nullptr;
};

#endif // MAINMENU_WIDGET_H
