#include "mainmenu_widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


GameModeMenuWidget::GameModeMenuWidget(const AplicationManager *sr, QWidget *parent)//конструктор меню выбора режима игры
    : QWidget(parent)
{
    gameVsBotButton = new QPushButton("Игра против бота", this);
    localGameButton = new QPushButton("Локальная игра", this);

    QVBoxLayout* menuLayot = new QVBoxLayout(this);
    menuLayot->addWidget(gameVsBotButton);
    menuLayot->addWidget(localGameButton);

    connect(gameVsBotButton, QPushButton::clicked, sr, AplicationManager::gameStart);//при нажатии на кнопку игры против бота, открытвается игра против бота
    connect(localGameButton, QPushButton::clicked, sr, AplicationManager::openLocalhostMenu);//при нажатии нак кнопку локальной игры открывается меню сетевого подключения
}

GameModeMenuWidget::~GameModeMenuWidget(){

}

MainMenuWidget::MainMenuWidget(const AplicationManager *sr, QWidget *parent)//конструктор глвного меню
    : QWidget(parent)
{
    gameButton = new QPushButton("Играть", this);
    aplicationCloseButton = new QPushButton("Выйти на рабочий стол", this);

    QVBoxLayout* menuLayot = new QVBoxLayout();
    menuLayot->addWidget(gameButton);
    menuLayot->addWidget(aplicationCloseButton);

    gameModeMenu = new GameModeMenuWidget(sr, this);

    QHBoxLayout* hbox = new QHBoxLayout(this);
    hbox->addLayout(menuLayot);
    hbox->addWidget(gameModeMenu);

    hideAllDropDownMenu();

    //при нажатии на кнопку играть открытвается меню режима игры
    connect(gameButton, QPushButton::clicked, this, MainMenuWidget::openGameModeMenu);
    //при нажатии выхода из игры закрывается приложение
    connect(aplicationCloseButton, QPushButton::clicked, sr, AplicationManager::aplicationClose);
    //при нажатии на esc скрываются вылезающие меню
    connect(this, MainMenuWidget::escPressed, this, MainMenuWidget::hideAllDropDownMenu);
}

void MainMenuWidget::openGameModeMenu()//открытвает меню вырбора режима игры
{
    hideAllDropDownMenu();
    gameModeMenu->show();
}

void MainMenuWidget::hideAllDropDownMenu()//скрывает все выползающие меню(по задумке их должно было быть несколько)
{
    gameModeMenu->hide();
}


MainMenuWidget::~MainMenuWidget()
{

}

