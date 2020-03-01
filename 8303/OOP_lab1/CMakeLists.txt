cmake_minimum_required(VERSION 3.15)
project(OOP_lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP_lab1 main.cpp Point.cpp Point.h GameField.cpp GameField.h GameFieldIterator.h Unit.cpp Unit.h Armor.cpp Armor.h Cape.h LeatherArmor.h IronArmor.h LaminarArmor.h FireMage.h IceMage.h Weapon.cpp Weapon.h FireBall.h IceStorm.h Archer.h Sniper.h CrossBowMan.h Vikings.h Berserk.h SwordMan.h UnitFactory.h VikingsFactory.h ArcherFactory.h WizardFactory.h Bow.h Axe.h Sword.h)