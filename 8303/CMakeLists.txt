cmake_minimum_required(VERSION 3.15)
project(OOP_lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP_lab1 main.cpp Point.cpp Point.h GameField.cpp GameField.h GameFieldIterator.h Unit.cpp Unit.h Armor.cpp Armor.h Cape.h LeatherArmor.h IronArmor.h LaminarArmor.h FireMage.h IceMage.h Weapon.cpp Weapon.h FireBall.h IceStorm.h Archer.h Sniper.h CrossBowMan.h Vikings.h Berserk.h SwordMan.h UnitFactory.h VikingsFactory.h ArcherFactory.h WizardFactory.h Bow.h Axe.h Sword.h FieldCell.cpp FieldCell.h LandscapeProxy.cpp LandscapeProxy.h Base.cpp Base.h GameObject.cpp GameObject.h Landscape.h Desert.h Ocean.h Snow.h NeutralObject.h ArcherStrategy.h VikingsStrategy.h NeutralObjectStrategy.h WizardStrategy.h UnitObserver.h BaseObserver.h WeaponFlyWeight.cpp WeaponFlyWeight.h ArmorFlyWeight.cpp ArmorFlyWeight.h House.h Hospital.h School.h Field.h)