include(../gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS +=     tst_lab2test.h \
    ../../../src/2.h

SOURCES +=     main.cpp \
    ../../../src/2.cpp
