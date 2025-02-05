#include "game_widget.h"

#include "QHBoxLayout"
#include "QVBoxLayout"
#include <QRandomGenerator>

//void function bot()
//{
//    int randomNumber = QRandomGenerator::global()->bounded(2);
//}

GameWidget::GameWidget(const SignalRepeater* sr,QWidget *parent)
    : QWidget(parent)
{
    rockButton = new QPushButton("Камень",this);
    scissorsButton = new QPushButton("Ножницы",this);
    paperButton = new QPushButton("Бумага",this);

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(rockButton);
    hbox->addWidget(scissorsButton);
    hbox->addWidget(paperButton);


    exitToMenuButton = new QPushButton("Выйти в главное меню",this);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addLayout(hbox);
    vbox->addWidget(exitToMenuButton);

    connect(exitToMenuButton, QPushButton::clicked, sr, SignalRepeater::exitToMenu);









}

GameWidget::~GameWidget()
{

}
