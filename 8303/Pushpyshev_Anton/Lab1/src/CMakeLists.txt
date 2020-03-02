cmake_minimum_required(VERSION 3.15)
project(Battle_For_Honor)

set(CMAKE_CXX_STANDARD 17)

add_executable(Battle_For_Honor main.cpp Units/Unit.cpp Units/Unit.h "Battle Field/Field.cpp" "Battle Field/Field.h" "Battle Field/Cell.cpp" "Battle Field/Cell.h" Units/Footman.cpp Units/Footman.h Units/Archer.cpp Units/Archer.h Units/Horseman.cpp Units/Horseman.h Units/Swordsman.cpp Units/Swordsman.h Units/Attributes.cpp Units/Attributes.h "Main Base/Base.cpp" "Main Base/Base.h" Units/Spearman.cpp Units/Spearman.h Units/Damage.cpp Units/Damage.h Units/Armour.cpp Units/Armour.h Units/HorseArcher.cpp Units/HorseArcher.h Units/SpearHorse.cpp Units/SpearHorse.h Units/LongBowman.cpp Units/LongBowman.h Units/Crossbows.cpp Units/Crossbows.h "Battle Field/FieldIterator.cpp" "Battle Field/FieldIterator.h")