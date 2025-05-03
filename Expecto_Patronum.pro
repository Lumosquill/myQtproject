QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bigdementor.cpp \
    bulletbase.cpp \
    chocolatefrog.cpp \
    dementor.cpp \
    enemybase.cpp \
    enemybullet.cpp \
    felix_felicis.cpp \
    gameobject.cpp \
    gameprogress.cpp \
    main.cpp \
    gamewidget.cpp \
    mygv.cpp \
    player.cpp \
    playerbullet.cpp \
    spider.cpp \
    thoughtbubble.cpp \
    timeturner.cpp

HEADERS += \
    bigdementor.h \
    bulletbase.h \
    chocolatefrog.h \
    dementor.h \
    enemybase.h \
    enemybullet.h \
    felix_felicis.h \
    gameobject.h \
    gameprogress.h \
    gamewidget.h \
    mygv.h \
    player.h \
    playerbullet.h \
    spider.h \
    thoughtbubble.h \
    timeturner.h

FORMS += \
    gamewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
