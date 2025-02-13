#include "mainmenu_widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


GameModeMenuWidget::GameModeMenuWidget(const SignalRepeater *sr, QWidget *parent)
    : QWidget(parent)
{
    gameVsBotButton = new QPushButton("Игра против бота", this);
    localGameButton = new QPushButton("Локальная игра", this);

    QVBoxLayout* menuLayot = new QVBoxLayout(this);
    menuLayot->addWidget(gameVsBotButton);
    menuLayot->addWidget(localGameButton);

    connect(gameVsBotButton, QPushButton::clicked, sr, SignalRepeater::gameStart);
    connect(localGameButton, QPushButton::clicked, sr, SignalRepeater::openLocalhostMenu);
}

GameModeMenuWidget::~GameModeMenuWidget(){

}

MainMenuWidget::MainMenuWidget(const SignalRepeater *sr, QWidget *parent)
    : QWidget(parent)
{
//    qDebug() << "Main menu open";

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

    connect(gameButton, QPushButton::clicked, this, MainMenuWidget::openGameModeMenu);
    connect(aplicationCloseButton, QPushButton::clicked, sr, SignalRepeater::aplicationClose);
    connect(this, MainMenuWidget::escPressed, this, MainMenuWidget::hideAllDropDownMenu);
//    qDebug() <<'asd';
}

void MainMenuWidget::openGameModeMenu()
{
    hideAllDropDownMenu();
    gameModeMenu->show();
}

void MainMenuWidget::hideAllDropDownMenu()
{
    gameModeMenu->hide();
}


MainMenuWidget::~MainMenuWidget()
{

}

