#-------------------------------------------------
#
# Project created by QtCreator 2019-05-01T16:02:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loggincategories.cpp \
    my_except.cpp \
    interface_node.cpp \
    edge.cpp \
    graphwidget.cpp

HEADERS  += mainwindow.h \
    personalclass.h \
    save.h \
    startinit.h \
    loggincategories.h \
    my_except.h \
    strings.h \
    logger.h \
    controller.h \
    edge.h \
    graphwidget.h \
    mynode.h \
    node.h

FORMS    += mainwindow.ui
