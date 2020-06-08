#ifndef OOP_HALBERDIER_H
#define OOP_HALBERDIER_H
#include "FootTroops.h"
#include "../FactoryMethod.h"

class Halberdier : public FootTroops{
public:
    Halberdier() {
        setAttributes(100, 100, 100);
        unitName = HALBERDIER;
    };
    char getName() final {return 'i';};
    Unit& operator+=(NeutralObject &object) final;
};

class HalberdierFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override {
        return new Halberdier();
    };
};
#endif //OOP_HALBERDIER_H
