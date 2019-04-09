QT += core
QT -= gui

CONFIG += c++11

TARGET = Lab2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    point.cpp \
    shape.cpp \
    square.cpp \
    regularpentagon.cpp \
    ellipse.cpp

HEADERS += \
    point.h \
    shape.h \
    square.h \
    regularpentagon.h \
    color.h \
    ellipse.h
