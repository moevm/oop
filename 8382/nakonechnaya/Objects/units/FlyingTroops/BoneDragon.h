#ifndef OOP_BONEDRAGON_H
#define OOP_BONEDRAGON_H
#include "FlyingTroops.h"
#include "../FactoryMethod.h"

class BoneDragon : public FlyingTroops{
public:
    BoneDragon() {
        setAttributes(100, 100, 100);
        unitName = BONE_DRAGON;
    };
    char getName() final {return 'i';};
    Unit& operator+=(NeutralObject &object) final;
};

class BoneDragonFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override {
        return new BoneDragon();
    };
};
#endif //OOP_BONEDRAGON_H
