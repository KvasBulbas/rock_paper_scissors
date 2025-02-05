#include "mainmenu_widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

MainMenuWidget::MainMenuWidget(const SignalRepeater *sr, QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "Main menu open";

    gameVsBotButton = new QPushButton("Игра против бота", this);
    localGameButton = new QPushButton("Локальная игра", this);
    aplicationCloseButton = new QPushButton("Выйти на рабочий стол", this);

    QVBoxLayout* menuLayot = new QVBoxLayout(this);
    menuLayot->addWidget(gameVsBotButton);
    menuLayot->addWidget(localGameButton);
    menuLayot->addWidget(aplicationCloseButton);
//    menuLayot->addStretch();

//    QHBoxLayout* hbox = new QHBoxLayout(this);
//    hbox->addLayout(menuLayot);
    connect(gameVsBotButton, QPushButton::clicked, sr, SignalRepeater::gameStart);
    connect(aplicationCloseButton, QPushButton::clicked, sr, SignalRepeater::aplicationClose);
}


MainMenuWidget::~MainMenuWidget()
{

}
