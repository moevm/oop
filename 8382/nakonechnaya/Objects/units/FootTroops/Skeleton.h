#ifndef OOP_SKELETON_H
#define OOP_SKELETON_H
#include "FootTroops.h"
#include "../FactoryMethod.h"

class Skeleton : public FootTroops{
public:
    Skeleton() {
        setAttributes(100, 100, 100);
        unitName = SKELETON;
    };
    char getName() final {return 'i';};
    Unit& operator+=(NeutralObject &object) final;
};

class SkeletonFactoryMethod : public FactoryMethod{
public:
    Unit* createUnit() const override {
        return new Skeleton();
    };
};
#endif //OOP_SKELETON_H
