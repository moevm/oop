#-------------------------------------------------
#
# Project created by QtCreator 2020-02-17T21:35:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    iterator.cpp \
    gamefield.cpp \
    Units/unit.cpp \
    Units/Archers/archers.cpp \
    Units/Archers/flatbow.cpp \
    Units/Archers/longbow.cpp \
    Units/Cavalry/cavalry.cpp \
    Units/Cavalry/dragoon.cpp \
    Units/Cavalry/hussar.cpp \
    Units/Infantry/infantry.cpp \
    Units/Infantry/spearman.cpp \
    Units/Infantry/swordsman.cpp \
    base.cpp \
    compositeunit.cpp \
    subject.cpp \


HEADERS += \
        mainwindow.h \
    iterator.h \
    gamefield.h \
    Units/unit.h \
    attributes.h \
    Units/Archers/archers.h \
    Units/Archers/flatbow.h \
    Units/Archers/longbow.h \
    Units/Cavalry/cavalry.h \
    Units/Cavalry/dragoon.h \
    Units/Cavalry/hussar.h \
    Units/Infantry/infantry.h \
    Units/Infantry/spearman.h \
    Units/Infantry/swordsman.h \
    UnitsFactory/archersfactory.h \
    UnitsFactory/cavalryfactory.h \
    UnitsFactory/infantryfactory.h \
    UnitsFactory/unitfactory.h \
    Landscapes/forests.h \
    Landscapes/landscape.h \
    Landscapes/mountains.h \
    Landscapes/rivers.h \
    Landscapes/landscapeprotected.h \
    base.h \
    observer.h \
    subject.h \
    compositeunit.h \
    NeutralObject/armor.h \
    NeutralObject/medicine.h \
    NeutralObject/neutralobject.h \
    NeutralObject/poison.h \
    NeutralObject/weapon.h \

FORMS += \
        mainwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Lab1.pro
