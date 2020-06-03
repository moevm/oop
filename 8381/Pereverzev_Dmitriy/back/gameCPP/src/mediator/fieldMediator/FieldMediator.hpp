

#ifndef FieldMediator_hpp
#define FieldMediator_hpp

#include <stdio.h>
#include <iostream>
#include "../Mediator.hpp"
#include "../../objects/combatObject/CombatObject.hpp"
#include "../../field/Field.hpp"

class FieldMediator : public Mediator
{
private:
    void interactionObjObj(Object *object1, Object *object2);
    void battle(CombatObject *object1, CombatObject *object2);

public:
    void interactionObjObj(Field *field, unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber) override;
};

#endif /* FieldMediator_hpp */
