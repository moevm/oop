#ifndef DAMAGEMEDIATOR_H
#define DAMAGEMEDIATOR_H
#include "Mediator.h"
#include "../Object.h"

class DamageMediator : public Mediator
{
public:

    void setObject1(Object*);

    void setObject2(Object*);

    void attack(Object*) const override;

protected:

    Object *obj1;

    Object *obj2;
};


#endif // DAMAGEMEDIATOR_H
