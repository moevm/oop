#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += SFML_STATIC

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


LIBS += -L"C:\SFML-2.5.1\lib"
LIBS += -L"C:\SFML-2.5.1\bin"

CONFIG(release, debug|release):
{
#audio libs
LIBS += -lsfml-audio
LIBS += -lopenal32
LIBS += -lFlac
LIBS += -lvorbisenc
LIBS += -lvorbisfile
LIBS += -lvorbis
LIBS += -logg

#SFML-Graphics Libs
LIBS += -lsfml-graphics
LIBS += -lfreetype

#SFML-Network libs
LIBS += -lsfml-network
LIBS += -lws2_32

#SFML-Window libs
LIBS += -lsfml-window
LIBS += -lopengl32
LIBS += -lgdi32

#SFML-system libs
LIBS += -lsfml-system
LIBS += -lwinmm
}

CONFIG(debug, debug|release):
{
#audio libs
LIBS += -lsfml-audio-d
LIBS += -lopenal32
LIBS += -lFlac
LIBS += -lvorbisenc
LIBS += -lvorbisfile
LIBS += -lvorbis
LIBS += -logg

#SFML-Graphics Libs
LIBS += -lsfml-graphics-d
LIBS += -lfreetype

#SFML-Network libs
LIBS += -lsfml-network-d
LIBS += -lws2_32

#SFML-Window libs
LIBS += -lsfml-window-d
LIBS += -lopengl32
LIBS += -lgdi32

#SFML-system libs
LIBS += -lsfml-system-d
LIBS += -lwinmm
}

#WINDOWS
INCLUDEPATH += "C:\SFML-2.5.1\include"
DEPENDPATH += "C:\SFML-2.5.1\include"


SOURCES += \
    cells.cpp \
    field.cpp \
    main.cpp \
    point.cpp \
    units.cpp \
    weapon.cpp

HEADERS += \
    cells.h \
    field.h \
    point.h \
    units.h \
    weapon.h

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
