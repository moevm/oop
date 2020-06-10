QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    ChainOfResonsibility/ChainOfResonsibility.cpp \
    Command/AddBaseCommand.cpp \
    Command/AttackUnitCommand.cpp \
    Command/Command.cpp \
    Command/CreateUnitToBaseCommand.cpp \
    Command/DeathUnitCommand.cpp \
    Command/DestroyBaseCommand.cpp \
    Command/EntryFromBaseCommand.cpp \
    Command/Invoker.cpp \
    Command/MoveUnitCommand.cpp \
    CreateFieldWindow.cpp \
    Field.cpp \
    Game.cpp \
    GameCell.cpp \
    GameField.cpp \
    Landscapes/Proxy/LavaProxy.cpp \
    Landscapes/Proxy/Proxy.cpp \
    Logger/Adapter/Adapter.cpp \
    Logger/Logger.cpp \
    Logger/LoggerEmpty.cpp \
    Logger/LoggerFile.cpp \
    Logger/LoggerTerminal.cpp \
    Memento/GameSaveLoad.cpp \
    Memento/Memento.cpp \
    Neuturals/Pack.cpp \
    Neuturals/Strategy/Strategy.cpp \
    Objects/Linker/Linker.cpp \
    Objects/Mediator/DamageMediator.cpp \
    Objects/Mediator/Mediator.cpp \
    Objects/Observer/Observer.cpp \
    Players/Players2.cpp \
    Players/Players3.cpp \
    Rules/Rule1.cpp \
    Rules/Rule2.cpp \
    Rules/States.cpp \
    Settings.cpp \
    exceptions/doubleplacefield.cpp \
    exceptions/invalidfielloadingexception.cpp \
    main.cpp \
    MainWindow.cpp \
    MyGraphicsView.cpp \
    Landscapes/Landscape.cpp \
    Landscapes/Lava.cpp \
    Landscapes/Rock.cpp \
    Landscapes/Water.cpp \
    Objects/Object.cpp \
    Objects/Base.cpp \
    Objects/Attributes.cpp \
    Objects/Units/Archer.cpp \
    Objects/Units/Centaur.cpp \
    Objects/Units/LongRange.cpp \
    Objects/Units/Panzer.cpp \
    Objects/Units/Rider.cpp \
    Objects/Units/ShortRange.cpp \
    Objects/Units/SpearMan.cpp \
    Objects/Units/SwordsMan.cpp \
    Objects/Units/Unit.cpp \
    Objects/Units/Wizard.cpp \
    Neuturals/ArmorPack.cpp \
    Neuturals/DamagePack.cpp \
    Neuturals/HealthPack.cpp \
    Neuturals/ManaPack.cpp \
    Objects/AbstractFactory/LongRangeFactory.cpp \
    Objects/AbstractFactory/RiderFactory.cpp \
    Objects/AbstractFactory/ShortRangeFactory.cpp

HEADERS += \
    ChainOfResonsibility/ChainOfResonsibility.h \
    Command/AddBaseCommand.h \
    Command/AttackUnitCommand.h \
    Command/Command.h \
    Command/Commands.h \
    Command/CreateUnitToBaseCommand.h \
    Command/DeathUnitCommand.h \
    Command/DestroyBaseCommand.h \
    Command/EntryFromBaseCommand.h \
    Command/Invoker.h \
    Command/MoveUnitCommand.h \
    CreateFieldWindow.h \
    Field.h \
    Game.h \
    GameCell.h \
    GameField.h \
    Landscapes/Proxy/LavaProxy.h \
    Landscapes/Proxy/Proxy.h \
    Logger/Adapter/Adapter.h \
    Logger/Logger.h \
    Logger/LoggerEmpty.h \
    Logger/LoggerFile.h \
    Logger/LoggerTerminal.h \
    MainWindow.h \
    Memento/GameSaveLoad.h \
    Memento/Memento.h \
    MyGraphicsView.h \
    Landscapes/Landscape.h \
    Landscapes/Lava.h \
    Landscapes/Rock.h \
    Landscapes/Water.h \
    Neuturals/Pack.h \
    Neuturals/Packs.h \
    Neuturals/Strategy/Strategy.h \
    Objects/AbstractFactory/UnitsAbstractFactory.h \
    Objects/Linker/Linker.h \
    Objects/Mediator/DamageMediator.h \
    Objects/Mediator/Mediator.h \
    Objects/Object.h \
    Objects/Base.h \
    Objects/Attributes.h \
    Objects/Observer/Observer.h \
    Objects/Units/Archer.h \
    Objects/Units/Centaur.h \
    Objects/Units/LongRange.h \
    Objects/Units/Panzer.h \
    Objects/Units/Rider.h \
    Objects/Units/ShortRange.h \
    Objects/Units/SpearMan.h \
    Objects/Units/SwordsMan.h \
    Objects/Units/Unit.h \
    Objects/Units/Units.h \
    Objects/Units/Wizard.h \
    Neuturals/ArmorPack.h \
    Neuturals/DamagePack.h \
    Neuturals/HealthPack.h \
    Neuturals/ManaPack.h \
    Objects/AbstractFactory/LongRangeFactory.h \
    Objects/AbstractFactory/RiderFactory.h \
    Objects/AbstractFactory/ShortRangeFactory.h \
    Players/Players2.h \
    Players/Players3.h \
    Rules/Rule1.h \
    Rules/Rule2.h \
    Rules/States.h \
    Settings.h \
    exceptions/doubleplacefield.h \
    exceptions/invalidfielloadingexception.h

FORMS += \
    createfieldwindow.ui \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
