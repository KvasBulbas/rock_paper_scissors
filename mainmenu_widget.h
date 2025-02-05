#ifndef MAINMENU_WIDGET_H
#define MAINMENU_WIDGET_H

#include "signalrepeater.h"

#include <QDebug>

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QKeyEvent>


class SignalRepeater;

class GameModeMenuWidget : public QWidget
{
    Q_OBJECT
public:
    GameModeMenuWidget(const SignalRepeater *sr, QWidget *parent = nullptr);
    ~GameModeMenuWidget();

private:
    QPushButton* gameVsBotButton = nullptr;
    QPushButton* localGameButton = nullptr;
};

class MainMenuWidget : public QWidget
{
    Q_OBJECT
public:
    MainMenuWidget(const SignalRepeater* sr, QWidget *parent = nullptr);
    ~MainMenuWidget();

signals:
    void escPressed();

public slots:
    void openGameModeMenu();
    void hideAllDropDownMenu();

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Escape) {
            emit escPressed();
        }
    }

private:
    GameModeMenuWidget* gameModeMenu = nullptr;

    QPushButton* gameButton = nullptr;
    QPushButton* aplicationCloseButton = nullptr;
};




#endif // MAINMENU_WIDGET_H
