#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include "aplicationmanager.h"

#include <QDebug>

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QKeyEvent>



class AplicationManager;

//Меню выбора режима игры. Можно зыкрать нажав esc
class GameModeMenuWidget : public QWidget
{
    Q_OBJECT
public:
    GameModeMenuWidget(const AplicationManager *sr, QWidget *parent = nullptr);
    ~GameModeMenuWidget();

private:
    QPushButton* gameVsBotButton = nullptr;
    QPushButton* localGameButton = nullptr;
};


/*Класс виджета главного меню. Предостваляет интрефейс главного меню с кнопками. Взаимодействуйет с остальным приложением
через AplicationManager. С помощью этого класса можно запустить игру с ботом, или открыть меню подлкючения, или
закрыть приложение. Также хранит в себе меню вылезающее меню в выбыром режима игры*/
class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    MainMenuWidget(const AplicationManager* sr, QWidget *parent = nullptr);
    ~MainMenuWidget();

signals:
    void escPressed();//сигнал вызывающийся при нажатии esc

public slots:
    void openGameModeMenu();
    void hideAllDropDownMenu();

protected:
    void keyPressEvent(QKeyEvent *event) override//перегруженый метод из QWidget, позволящий регситрировать нажатие esc
    {
        if (event->key() == Qt::Key_Escape)
            emit escPressed();
    }

private:
    GameModeMenuWidget* gameModeMenu = nullptr;

    QPushButton* gameButton = nullptr;
    QPushButton* aplicationCloseButton = nullptr;
};




#endif // MAINMENU_WIDGET_H
