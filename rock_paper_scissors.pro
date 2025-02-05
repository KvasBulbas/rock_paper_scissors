QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game_widget.cpp \
    gameclient.cpp \
    gameprocess.cpp \
    gameserver.cpp \
    main.cpp \
    mainmenu_widget.cpp \
    mainwindow_widget.cpp \
    signalrepeater.cpp

HEADERS += \
    game_widget.h \
    gameclient.h \
    gameprocess.h \
    gameserver.h \
    mainmenu_widget.h \
    mainwindow_widget.h \
    signalrepeater.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
