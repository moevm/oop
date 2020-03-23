#include "mediator.h"
#include "GameField/gamefield.h"



Mediator::Mediator(GameField* field)
{
    this->field = field;
}


bool Mediator::notify(Unit* unit, int x, int y)
{
    if (x < 0 || x >= field->getWidth() ||
            y < 0 || y >= field->getHeight()) {
        return false;
    }

    if (field->getCell(x, y)->isEmpty()){
        if (field->getCell(x, y)->getlandscape()->canMove(unit)) {
            field->getCell(unit->getCoordiante().x,
                           unit->getCoordiante().y)->deleteUnit();

            field->getCell(x, y)->getlandscape()->hurtUnit(unit);
            field->getCell(x, y)->addUnit(unit);

            (*field->getCell(x, y)->getNeutralObject())(unit);
            field->getCell(x, y)->deleteNeutralObject();

            return true;
        }
    }

    return false;
}
