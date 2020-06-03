cmake_minimum_required(VERSION 3.10)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

file(
        GLOB SOURCES
        *.h *.cpp
)

add_executable(
        OOP ${SOURCE_FILES} ${SOURCES}

        # info Logging
        Logging/Logger.h
        Logging/LoggerFormat.h Logging/LoggerFormat.cpp
        Logging/LoggerProxy.h Logging/LoggerProxy.cpp
        Logging/LoggingFile.h Logging/LoggingFile.cpp
        Logging/LoggingTerminal.h Logging/LoggingTerminal.cpp
        Logging/NoLogging.h

        # info Saving/Loading game
        Snapshot/GameLoad.h Snapshot/GameLoad.cpp
        Snapshot/GameSave.h Snapshot/GameSave.cpp
        Snapshot/SnapshotBase.h Snapshot/SnapshotBase.cpp
        Snapshot/SnapshotField.h Snapshot/SnapshotField.cpp
        Snapshot/SnapshotGame.h Snapshot/SnapshotGame.cpp
        Snapshot/SnapshotUnit.h Snapshot/SnapshotUnit.cpp

        # info All Unit's classes
        Unit/Elfs.h Unit/Elfs.cpp
        Unit/Men.h Unit/Men.cpp
        Unit/Orcs.h Unit/Orcs.cpp
        Unit/Warrior.h Unit/Warrior.cpp

        Unit/UnitFactory.h Unit/UnitFactory.cpp

        # info All Field's classes
        Field/Cell.h Field/Cell.cpp
        Field/Field.h Field/Field.cpp
        Field/Iterator.h Field/Iterator.cpp

        Field/Landscape/Landscape.h Field/Landscape/Landscape.cpp
        Field/Landscape/Proxy.h Field/Landscape/Proxy.cpp

        Field/NeutralObject/NeutralObject.h Field/NeutralObject/NeutralObject.cpp
        Field/NeutralObject/Context.h Field/NeutralObject/Context.cpp

        # info All Base's classes
        Base/Base.h Base/Base.cpp
        Base/BaseFlyWeight.h Base/BaseFlyWeight.cpp
        Base/BaseIObserver.h Base/BaseIObserver.cpp
        Base/BaseSubject.h Base/BaseSubject.cpp

        # info All Interfaces
        Interfaces/Game.h Interfaces/Game.cpp
        Interfaces/Command.h Interfaces/Command.cpp
        Interfaces/Mediator.h Interfaces/Mediator.cpp

        # info Game's classes
        Game/GameSingleton.h Game/GameSingleton.cpp
        Game/Rules/Rules.h
        Game/Rules/RuleWith.h Game/Rules/RuleWith.cpp
        Game/Rules/RuleWithout.h Game/Rules/RuleWithout.cpp

        Game/States/State.h
        Game/States/State1.h Game/States/State1.cpp
        Game/States/State2.h Game/States/State2.cpp
        Game/States/StateContext.h Game/States/StateContext.cpp
)