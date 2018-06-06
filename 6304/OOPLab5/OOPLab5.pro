TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    Ellipse.cpp \
    Line.cpp \
    Pentagon.cpp \
    Point.cpp \
    Shape.cpp

HEADERS += \
    Ellipse.h \
    Line.h \
    Pentagon.h \
    Point.h \
    Shape.h \
    shared_ptr.h
