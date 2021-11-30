QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    render/render.cpp \
    render/visualcard.cpp \
    render/visualplayer.cpp \
    server/gameclient.cpp \
    server/gameserver.cpp \
    server/gameserverinterface.cpp \
    game/Card.cpp \
    game/GameEngine.cpp \
    game/Player.cpp \

HEADERS += \
    mainwindow.h \
    render/render.h \
    render/visualcard.h \
    render/visualplayer.h \
    server/gameclient.h \
    server/gameserver.h \
    server/gameserverinterface.h \
    game/Card.h \
    game/GameEngine.h \
    game/Player.h \

FORMS += \
    mainwindow.ui

RESOURCES += \
    Res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
