QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Disable unused parameter warnings
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# Compiele flags
QMAKE_CXXFLAGS += -lstdc++fs

SOURCES += \
    AuxiliaryFunctionality/Exceptions/fieldexception.cpp \
    AuxiliaryFunctionality/TextColoring.cpp \
    AuxiliaryFunctionality/UnitMediators.cpp \
    Bases/BaseMaster.cpp \
    Bases/GameBase.cpp \
    Bases/HellBase.cpp \
    Bases/HellBaseBuilder.cpp \
    Bases/HumanBase.cpp \
    Bases/HumanBaseBuilder.cpp \
    Bases/UnitStorekeeper.cpp \
    GUI/command.cpp \
    GUI/gamewindow.cpp \
    GUI/mainwindow.cpp \
    GUI/visualizer.cpp \
    Game/FacadeMediator.cpp \
    Game/GameProcess/GamersState.cpp \
    Game/GameProcess/gameRules.cpp \
    Game/GameProcess/gameprocess.cpp \
    Game/Logging/Loggers/logadapter.cpp \
    Game/Logging/Loggers/loggers.cpp \
    Game/Logging/time.cpp \
    Game/Saving/gamemementocaretacker.cpp \
    Game/Saving/mementofiles.cpp \
    Game/UIFacade.cpp \
    Game/game.cpp \
    GameField/Cell.cpp \
    GameField/GameField.cpp \
    GameField/GameFieldProxy.cpp \
    Landscape/Champaign.cpp \
    Landscape/Forest.cpp \
    Landscape/Landscape.cpp \
    Landscape/Mountains.cpp \
    NeutralObjects/EnchantedRobe.cpp \
    NeutralObjects/EnergyPotion.cpp \
    NeutralObjects/LegendaryWeapon.cpp \
    NeutralObjects/NeutralObjectContext.cpp \
    NeutralObjects/Poison.cpp \
    Tests/examples.cpp \
    Units/CompositeUnit.cpp \
    Units/Creatures/Archer.cpp \
    Units/Creatures/Cerberus.cpp \
    Units/Creatures/Demon.cpp \
    Units/Creatures/Heck.cpp \
    Units/Creatures/Ifrit.cpp \
    Units/Creatures/Knight.cpp \
    Units/Creatures/Magician.cpp \
    Units/Creatures/Peasant.cpp \
    Units/Creatures/Succubus.cpp \
    Units/Creatures/Swordsman.cpp \
    Units/Unit.cpp \
    main.cpp

HEADERS += \
    AuxiliaryFunctionality/Array2D.h \
    AuxiliaryFunctionality/EnumToString.h \
    AuxiliaryFunctionality/Exceptions/baseexception.h \
    AuxiliaryFunctionality/Exceptions/fieldexception.h \
    AuxiliaryFunctionality/GameFieldIterator.h \
    AuxiliaryFunctionality/TextColoring.h \
    AuxiliaryFunctionality/UnitMediators.h \
    AuxiliaryFunctionality/UnitObserver.h \
    AuxiliaryFunctionality/UnitSubject.h \
    AuxiliaryFunctionality/Vector.h \
    Bases/BaseBuilder.h \
    Bases/BaseMaster.h \
    Bases/GameBase.h \
    Bases/HellBase.h \
    Bases/HellBaseBuilder.h \
    Bases/HumanBase.h \
    Bases/HumanBaseBuilder.h \
    Bases/UnitStorekeeper.h \
    GUI/ICommand.h \
    GUI/IVisualizer.h \
    GUI/command.h \
    GUI/gamewindow.h \
    GUI/mainwindow.h \
    GUI/visualizer.h \
    Game/FacadeMediator.h \
    Game/GameProcess/GameRules.h \
    Game/GameProcess/GamersState.h \
    Game/GameProcess/gameprocess.h \
    Game/IFacadeMediator.h \
    Game/IGame.h \
    Game/Logging/ILogger.h \
    Game/Logging/Loggers/ILogAdapter.h \
    Game/Logging/Loggers/logadapter.h \
    Game/Logging/Loggers/loggers.h \
    Game/Logging/logfunctionality.h \
    Game/Logging/time.h \
    Game/Saving/ICaretacker.h \
    Game/Saving/SaveStuctures.h \
    Game/Saving/gamemementocaretacker.h \
    Game/Saving/mementofiles.h \
    Game/UIFacade.h \
    Game/game.h \
    GameField/Cell.h \
    GameField/Coords.h \
    GameField/GameField.h \
    GameField/GameFieldProxy.h \
    GameField/IGameField.h \
    InformationHeaders/commandPar.h \
    InformationHeaders/constPar.h \
    InformationHeaders/guiPar.h \
    InformationHeaders/unitPar.h \
    Landscape/Champaign.h \
    Landscape/Forest.h \
    Landscape/Landscape.h \
    Landscape/Mountains.h \
    NeutralObjects/EnchantedRobe.h \
    NeutralObjects/EnergyPotion.h \
    NeutralObjects/LegendaryWeapon.h \
    NeutralObjects/NeutralObject.h \
    NeutralObjects/NeutralObjectContext.h \
    NeutralObjects/Poison.h \
    Tests/examples.h \
    Units/CompositeUnit.h \
    Units/Creatures/Archer.h \
    Units/Creatures/Cerberus.h \
    Units/Creatures/Demon.h \
    Units/Creatures/Heck.h \
    Units/Creatures/Ifrit.h \
    Units/Creatures/Knight.h \
    Units/Creatures/Magician.h \
    Units/Creatures/Peasant.h \
    Units/Creatures/Succubus.h \
    Units/Creatures/Swordsman.h \
    Units/ICannonFodder.h \
    Units/ICavalry.h \
    Units/IInfantry.h \
    Units/IShooter.h \
    Units/IUnitAttack.h \
    Units/IWizard.h \
    Units/ObjectFactory.h \
    Units/Unit.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
