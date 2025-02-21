#include "mainmenu_widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


MainMenuWidget::MainMenuWidget(const AplicationManager *aplicationManager, QWidget *parent)//конструктор глвного меню
    : QWidget(parent)
{
    gameButton = new QPushButton("Локальная игра", this);
    aplicationCloseButton = new QPushButton("Выйти на рабочий стол", this);

    QVBoxLayout* menuLayot = new QVBoxLayout(this);
    menuLayot->addWidget(gameButton);
    menuLayot->addWidget(aplicationCloseButton);

    //при нажатии на кнопку играть открытвается меню режима игры
    connect(gameButton, &QPushButton::clicked, aplicationManager, &AplicationManager::openLocalhostMenu);
    //при нажатии выхода из игры закрывается приложение
    connect(aplicationCloseButton, &QPushButton::clicked, aplicationManager, &AplicationManager::aplicationClose);
    //при нажатии на esc скрываются вылезающие меню
}

MainMenuWidget::~MainMenuWidget()
{

}

