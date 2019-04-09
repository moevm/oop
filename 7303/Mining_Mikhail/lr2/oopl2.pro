QT += core
QT -= gui

CONFIG += c++11

TARGET = oopl2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    circle.cpp \
    ellipse.cpp \
    ellipse_sector.cpp \
    shape.cpp


HEADERS += ellipse.h \
    circle.h \
    ellipse_sector.h \
    shape.h
