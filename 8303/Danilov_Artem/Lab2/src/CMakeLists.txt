cmake_minimum_required(VERSION 3.16)
project(gameOfTheYear)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Base)
include_directories(Field)
include_directories(Landscape)
include_directories(NeutralObject)
include_directories(Units)
include_directories(Units/Factory)
include_directories(Units/Melee)
include_directories(Units/Range)
include_directories(Units/Support)

add_executable(gameOfTheYear
        Base/base.cpp
        Base/base.h
        Base/composite.h
        Field/field.cpp
        Field/field.h
        Field/fieldItem.cpp
        Field/fieldItem.h
        Landscape/landscape.h
        Landscape/proxy.cpp
        Landscape/proxy.h
        NeutralObject/armor.h
        NeutralObject/context.h
        NeutralObject/curse.h
        NeutralObject/elixir.h
        NeutralObject/neutralObj.h
        NeutralObject/weapon.h
        Units/Factory/direFactory.h
        Units/Factory/radiantFactory.h
        Units/Factory/unitFactory.h
        Units/Melee/knight.h
        Units/Melee/melee.h
        Units/Melee/ork.h
        Units/Range/chimera.h
        Units/Range/dragon.h
        Units/Range/range.h
        Units/Support/dryad.h
        Units/Support/support.h
        Units/Support/witch.h
        Units/characteristics.cpp
        Units/characteristics.h
        Units/unit.cpp
        Units/unit.h
        libraries.h
        main.cpp
        moveMediator.h
        observer.h
        subject.cpp
        subject.h)
