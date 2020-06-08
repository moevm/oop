#ifndef OOP_ARCHER_H
#define OOP_ARCHER_H
#include "RangedTroops.h"
#include "../FactoryMethod.h"

class Archer : public RangedTroops{
public:
    Archer() {
        setAttributes(100, 100, 100);
        unitName = ARCHER;
    };
    char getName() final {return 'i';};
    Unit& operator+=(NeutralObject &object) final;
};

class ArcherFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override {
        return new Archer();
    };
};
#endif //OOP_ARCHER_H
