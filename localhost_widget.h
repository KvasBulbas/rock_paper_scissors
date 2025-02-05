#ifndef LOCALHOSTWIDGET_H
#define LOCALHOSTWIDGET_H

#include "signalrepeater.h"

#include <QWidget>
#include <QPushButton>

class SignalRepeater;

class LocalHostWidget : public QWidget
{
    Q_OBJECT
public:
    LocalHostWidget(const SignalRepeater *sr, QWidget *parent = nullptr);
    ~LocalHostWidget();


private:
    QPushButton* createLobbyButton = nullptr;
    QPushButton* findLobbyButton = nullptr;
    QPushButton* connectButton = nullptr;
    QPushButton* exitToMenuButton = nullptr;

};

#endif // LOCALHOSTWIDGET_H
