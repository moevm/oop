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
    Factory/archerfactory.cpp \
    Factory/dragonfactory.cpp \
    Factory/dwarffactory.cpp \
    Factory/harpyfactory.cpp \
    Factory/liveshieldfactory.cpp \
    Factory/swordsmanfactory.cpp \
        GameField/cellofgamefield.cpp \
        GameField/gamefield.cpp \
    GameField/gamefielditerator.cpp \
    Landscape/foglandscape.cpp \
    Landscape/grasslanscape.cpp \
    Landscape/proxylandscape.cpp \
    Landscape/spineslandscape.cpp \
    NeutralObject/Strategy/heallerstrategy.cpp \
    NeutralObject/Strategy/killerstrategy.cpp \
    NeutralObject/Strategy/nostrategy.cpp \
    NeutralObject/Strategy/updateheavyarmorstrategy.cpp \
    NeutralObject/Strategy/updatelightarmorstrategy.cpp \
    NeutralObject/Strategy/updatenoarmorstrategy.cpp \
    NeutralObject/heallerobject.cpp \
    NeutralObject/killerobject.cpp \
    NeutralObject/neutralobject.cpp \
    NeutralObject/noobject.cpp \
    NeutralObject/updatearmorobject.cpp \
        Unit/archer.cpp \
    Unit/base/base.cpp \
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
    Factory/archerfactory.h \
    Factory/dragonfactory.h \
    Factory/dwarffactory.h \
    Factory/harpyfactory.h \
    Factory/liveshieldfactory.h \
    Factory/swordsmanfactory.h \
    Factory/unitfactory.h \
        GameField/cellofgamefield.h \
        GameField/gamefield.h \
    GameField/gamefielditerator.h \
    Landscape/foglandscape.h \
    Landscape/grasslanscape.h \
    Landscape/landscape.h \
    Landscape/proxylandscape.h \
    Landscape/spineslandscape.h \
    NeutralObject/Strategy/heallerstrategy.h \
    NeutralObject/Strategy/killerstrategy.h \
    NeutralObject/Strategy/nostrategy.h \
    NeutralObject/Strategy/strategy.h \
    NeutralObject/Strategy/updateheavyarmorstrategy.h \
    NeutralObject/Strategy/updatelightarmorstrategy.h \
    NeutralObject/Strategy/updatenoarmorstrategy.h \
    NeutralObject/heallerobject.h \
    NeutralObject/killerobject.h \
    NeutralObject/neutralobject.h \
    NeutralObject/noobject.h \
    NeutralObject/updatearmorobject.h \
    Unit/IRegeneration.h \
        Unit/archer.h \
    Unit/base/base.h \
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
    idrawable.h \
    mediator.h \
        point2d.h \
