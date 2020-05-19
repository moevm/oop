cmake_minimum_required(VERSION 3.15)
project(OOP_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP_1 main.cpp Units/Unit.cpp Units/Unit.h Cell.cpp Cell.h Field.cpp Field.h Units/Wizard.cpp Units/Wizard.h Units/Flamen.cpp Units/Flamen.h Units/Thief.cpp Units/Thief.h Units/Warrior.cpp Units/Warrior.h Units/Dwarf.cpp Units/Dwarf.h Units/Necromancer.cpp Units/Necromancer.h Units/Paladin.cpp Units/Paladin.h Units/Elf.cpp Units/Elf.h Units/Bard.cpp Units/Bard.h Base.cpp Base.h Landscape.cpp Landscape.h Neutral.cpp Neutral.h Fabric.h Observer.h Subject.cpp Subject.h Facade.cpp Facade.h Handler.cpp Handler.h Command.cpp Command.h Logger.cpp Logger.h Adapter.cpp Adapter.h FileInOut.h ProxyLogger.cpp ProxyLogger.h SnapShot.cpp SnapShot.h Game.h Exception.h Rules.h State.h Rules.cpp)