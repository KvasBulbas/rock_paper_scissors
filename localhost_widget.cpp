#include "localhost_widget.h"
#include <QVBoxLayout>

LocalHostWidget::LocalHostWidget(const SignalRepeater *sr, QWidget *parent): QWidget(parent)
{
    createLobbyButton = new QPushButton("Создать лобби",this);
    findLobbyButton = new QPushButton("Найти лобби",this);
    connectButton = new QPushButton("Подключиться напрямую",this);
    exitToMenuButton = new QPushButton("Выйти в главное меню",this);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(createLobbyButton);
    vbox->addWidget(findLobbyButton);
    vbox->addWidget(connectButton);
    vbox->addWidget(exitToMenuButton);

    connect(exitToMenuButton, QPushButton::clicked, sr, SignalRepeater::exitToMenu);
}

LocalHostWidget::~LocalHostWidget()
{

}
