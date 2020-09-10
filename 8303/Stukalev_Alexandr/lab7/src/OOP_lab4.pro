QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        adapter.cpp \
        base.cpp \
        composit.cpp \
        facade.cpp \
        field.cpp \
        iterator.cpp \
        landscape.cpp \
        logging.cpp \
        main.cpp \
        mediator.cpp \
        neutralobj.cpp \
        observer.cpp \
        snapshot.cpp \
        units.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    adapter.h \
    chainofrespons.h \
    command.h \
    composit.h \
    facade.h \
    field.h \
    file.h \
    gameclass.h \
    infile.h \
    iterator.h \
    landscape.h \
    logging.h \
    mediator.h \
    myexeptions.h \
    neutralobj.h \
    observer.h \
    rules.h \
    snapshot.h \
    statics.h \
    units.h
