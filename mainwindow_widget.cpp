#include "mainwindow_widget.h"


#include <QDebug>

#include <QVBoxLayout>
#include <QHBoxLayout>


MainWindowWidget::MainWindowWidget(QWidget *parent)
    : QWidget(parent)
{

    sr = new SignalRepeater(this);

    mainMenu = new MainMenuWidget(sr,this);
    game = new GameWidget(sr ,this);
    localHostMenu = new LocalHostWidget(sr, this);

    stackedWidget = new QStackedWidget(this);

    stackedWidget->addWidget(mainMenu);
    stackedWidget->addWidget(game);
    stackedWidget->addWidget(localHostMenu);

//    stackedWidget->setCurrentIndex(1);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(stackedWidget, 0, Qt::AlignCenter);
//    layout->addStretch();

//    gameStartButton = new QPushButton("start game", this);
//    QVBoxLayout* menuLayot = new QVBoxLayout(this);
//    menuLayot->addWidget(gameStartButton);


//    exitToMenuButton = new QPushButton("exit to menu game", this);
//    exitToMenuButton->hide();

//    QVBoxLayout* gameLayout = new QVBoxLayout(this);
//    gameLayout->addWidget(exitToMenuButton);
//    inputLabel = new QLabel(("Enter a number:"), this);
//    inputEdit = new QLineEdit("",this);
//    outputLabel = new QLabel(("Result:"),this);
//    outputEdit = new QLineEdit("",this);
//    QVBoxLayout *vLayout1 = new QVBoxLayout(this);
//    vLayout1->addWidget(inputLabel);
//    vLayout1->addWidget(inputEdit);
//    vLayout1->addWidget(outputLabel);
//    vLayout1->addWidget(outputEdit);
//    vLayout1->addStretch();

//    connect(gameStartButton, QPushButton::clicked, this, Widget::gameStart);
}

MainWindowWidget::~MainWindowWidget()
{
    delete[] sr;
}

void MainWindowWidget::setWidget(const int index)
{
    stackedWidget->setCurrentIndex(index);
}



