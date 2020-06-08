#ifndef OOP_LICH_H
#define OOP_LICH_H
#include "RangedTroops.h"
#include "../FactoryMethod.h"

class Lich : public RangedTroops{
public:
    Lich() {
        setAttributes(100, 100, 100);
        unitName = LICH;
    };
    char getName() final {return 'i';};
    Unit& operator+=(NeutralObject &object) final;
};

class LichFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override {
        return new Lich();
    };
};
#endif //OOP_LICH_H
