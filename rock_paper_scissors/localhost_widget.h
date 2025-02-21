#ifndef LOCALHOSTWIDGET_H
#define LOCALHOSTWIDGET_H

#include "aplicationmanager.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTcpSocket>
#include <QKeyEvent>
#include <QLineEdit>
#include <QTextEdit>


class AplicationManager;

//класс виджета поля ввода адреса, по которому хотим подключиться
class AdressLineEdit : public QWidget
{
    Q_OBJECT
public:
    AdressLineEdit(AplicationManager *aplicationManager, QWidget *parent = nullptr);

public slots:
    void enterServerName();

private:
    QLineEdit* hostLineEdit = nullptr;
    QLineEdit* portLineEdit = nullptr;
    QLabel* colon = nullptr;

    ServerManager* serverManager = nullptr;
};


//класс виджета меню подключения. Через него можно создать сервер и подключиться к нему
class LocalHostWidget : public QWidget
{
    Q_OBJECT
public:
    LocalHostWidget(AplicationManager *aplicationManager, QWidget *parent = nullptr);
    ~LocalHostWidget();

signals:
    void escPressed();//сигнал срабатывающий при нажатии на esc

public slots:
    void createLobby();
    void clientConnect();
    void editCreatedMessage(const QString& serverAdresses, const QString& port);

private slots:
    void baseStateReturn();

private:
    void keyPressEvent(QKeyEvent *event) override//метод считывания нажатия на esc
    {
        if (event->key() == Qt::Key_Escape)
            emit escPressed();
    }

    QPushButton* createLobbyButton = nullptr;
    QPushButton* findLobbyButton = nullptr;
    QPushButton* connectButton = nullptr;
    QPushButton* exitToMenuButton = nullptr;

    QTextEdit* createLobbyMesage = nullptr;
    QLabel* connectionMesage = nullptr;

    AdressLineEdit* adressLineEdit = nullptr;

    ServerManager* serverManager = nullptr;

};

#endif // LOCALHOSTWIDGET_H
