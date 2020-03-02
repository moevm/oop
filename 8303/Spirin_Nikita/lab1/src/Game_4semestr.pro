#-------------------------------------------------
#
# Project created by QtCreator 2020-02-13T22:25:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game_4semestr
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamefield.cpp \
    unit.cpp \
    infantry.cpp \
    swordsman.cpp \
    factoryofunits.cpp \
    factoryofinfantry.cpp \
    factoryofshooters.cpp \
    archer.cpp \
    crossbowman.cpp \
    shooter.cpp \
    spearman.cpp \
    horseman.cpp \
    horsemanwithspear.cpp \
    horsemanwithsword.cpp \
    factoryohorsemen.cpp \
    point.cpp \
    pointofway.cpp \
    arrofpoints.cpp

HEADERS  += mainwindow.h \
    gamefield.h \
    unit.h \
    infantry.h \
    swordsman.h \
    factoryofunits.h \
    factoryofinfantry.h \
    factoryofshooters.h \
    archer.h \
    crossbowman.h \
    shooter.h \
    spearman.h \
    horseman.h \
    horsemanwithspear.h \
    horsemanwithsword.h \
    factoryofhorsemen.h \
    point.h \
    pointofway.h \
    arrofpoints.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
