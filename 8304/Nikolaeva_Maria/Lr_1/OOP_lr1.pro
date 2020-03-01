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
        Armor/heavyarmor.cpp \
        Armor/lightarmor.cpp \
        Armor/noarmor.cpp \
        GameField/cellofgamefield.cpp \
        GameField/gamefield.cpp \
        Unit/archer.cpp \
        Unit/dragon.cpp \
        Unit/dwarf.cpp \
        Unit/flyingunit.cpp \
        Unit/harpy.cpp \
        Unit/infantryunit.cpp \
        Unit/liveshield.cpp \
        Unit/standingunit.cpp \
        Unit/swordsman.cpp \
        Unit/unit.cpp \
        Weapon/ax.cpp \
        Weapon/bow.cpp \
        Weapon/claws.cpp \
        Weapon/fireball.cpp \
        Weapon/noweapon.cpp \
        Weapon/sword.cpp \
        main.cpp \
    mediator.cpp \
        point2d.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
        Armor/armor.h \
        Armor/heavyarmor.h \
        Armor/lightarmor.h \
        Armor/noarmor.h \
        GameField/cellofgamefield.h \
        GameField/gamefield.h \
        Unit/archer.h \
        Unit/dragon.h \
        Unit/dwarf.h \
        Unit/flyingunit.h \
        Unit/harpy.h \
        Unit/infantryunit.h \
        Unit/liveshield.h \
        Unit/standingunit.h \
        Unit/swordsman.h \
        Unit/unit.h \
        Weapon/ax.h \
        Weapon/bow.h \
        Weapon/claws.h \
        Weapon/fireball.h \
        Weapon/noweapon.h \
        Weapon/sword.h \
        Weapon/weapon.h \
    mediator.h \
        point2d.h \
