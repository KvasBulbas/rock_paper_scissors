#ifndef LOCALHOSTWIDGET_H
#define LOCALHOSTWIDGET_H

#include "signalrepeater.h"
//#include "gameclient.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTcpSocket>
#include <QKeyEvent>

class SignalRepeater;

class LocalHostWidget : public QWidget
{
    Q_OBJECT
public:
    LocalHostWidget(SignalRepeater *sr, QWidget *parent = nullptr);
    ~LocalHostWidget();

signals:
    void escPressed();

public slots:
    void createLobby();
    void clientConnect();
    void baseStateReturn();

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Escape) {
            emit escPressed();
        }
    }

private:
    QPushButton* createLobbyButton = nullptr;
    QPushButton* findLobbyButton = nullptr;
    QPushButton* connectButton = nullptr;
    QPushButton* exitToMenuButton = nullptr;

    QLabel* createLobbyMesage = nullptr;
    QLabel* connectionMesage = nullptr;

    ServerManager* serverManager = nullptr;
};

#endif // LOCALHOSTWIDGET_H
