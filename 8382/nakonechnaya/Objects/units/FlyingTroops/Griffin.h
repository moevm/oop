#ifndef OOP_GRIFFIN_H
#define OOP_GRIFFIN_H
#include "FlyingTroops.h"
#include "../FactoryMethod.h"

class Griffin : public FlyingTroops{
public:
    Griffin() {
        setAttributes(100, 100, 100);
        unitName = GRIFFIN;
    };
    char getName() final {return 'i';};
    Unit& operator+=(NeutralObject &object) final;
};

class GriffinFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override {
        return new Griffin();
    };
};
#endif //OOP_GRIFFIN_H
