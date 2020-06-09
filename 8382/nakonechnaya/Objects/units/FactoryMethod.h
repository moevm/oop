#ifndef OOP_FACTORYMETHOD_H
#define OOP_FACTORYMETHOD_H
#include "Unit.h"

class FactoryMethod {
public:
    virtual ~FactoryMethod(){};
    virtual Unit* createUnit() const = 0;
};
#endif //OOP_FACTORYMETHOD_H
