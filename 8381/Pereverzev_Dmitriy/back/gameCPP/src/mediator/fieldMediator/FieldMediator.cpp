#include "FieldMediator.hpp"

void FieldMediator::battle(CombatObject *object1, CombatObject *object2)
{
    double damage1 = object1->getDamage(),
           damage2 = object2->getDamage(),
           armor1 = object1->getArmor(),
           armor2 = object2->getArmor();

    object1->underAttack(damage2, armor2);
    object2->underAttack(damage1, armor1);
}
void FieldMediator::interactionObjObj(Object *object1, Object *object2)
{
    if (object1 == nullptr || object2 == nullptr)
        return;
    if (object2->getObjectType() >= 7)
    {
        *object2 + object1;
        return;
    }
    else if (object1->getPlayerID() == object2->getPlayerID())
    {
        
        
        
        return;
    }
    else
        battle((CombatObject *)object1, (CombatObject *)object2);
}
void FieldMediator::interactionObjObj(Field *field, unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber)
{
    if (!field->getFieldCell(toRowNumber, toColumnNumber).getLandscape()->checkAccessInteraction(field->getFieldCell(fromRowNumber, fromColumnNumber).getObject()->getObjectType()))
    {
        
        
        
        return;
    }
    
    
    
    interactionObjObj(field->getFieldCell(fromRowNumber, fromColumnNumber).getObject(), field->getFieldCell(toRowNumber, toColumnNumber).getObject());
}
