cmake_minimum_required(VERSION 3.15)
project(oop_labs)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "/home/mensch/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/mensch/SFML-2.5.1/lib")
set(SFML_DIR "/home/mensch/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(oop_labs main.cpp Field/Field.cpp Field/Field.h Object.cpp Object.h Point.cpp Point.h Units/Unit.cpp Units/Unit.h Units/Archers/Archer.cpp Units/Archers/Archer.h Units/Archers/Bowman.cpp Units/Archers/Bowman.h Units/Archers/Crossbowman.cpp Units/Archers/Crossbowman.h Units/Factories/UnitFactory.h Units/Swordsmen/Swordsman.cpp Units/Swordsmen/Swordsman.h Units/Swordsmen/Knight.cpp Units/Swordsmen/Knight.h Units/Swordsmen/Squire.cpp Units/Swordsmen/Squire.h Units/Wizards/Wizard.cpp Units/Wizards/Wizard.h Units/Wizards/Druid.cpp Units/Wizards/Druid.h Units/Wizards/Archmage.cpp Units/Wizards/Archmage.h Units/Factories/ArcherFactory.h Units/Factories/SwordsmenFactory.h Units/Factories/WizardFactory.h Field/FieldIterator.h Field/Cell.h)

target_link_libraries(oop_labs sfml-graphics sfml-window sfml-system)
