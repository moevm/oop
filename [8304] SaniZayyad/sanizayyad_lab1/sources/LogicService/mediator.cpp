#include "mediator.hpp"
#include "BattleField.hpp"
#include "unit.hpp"

Mediator::Mediator(std::shared_ptr<BattleField> battleField)
{
    this->battleField = battleField;
}


bool Mediator::notify(std::shared_ptr<Unit> unit,const std::string& action)
{
    Position2D currentPosition = unit->getPosition();
    FieldCell& currentCell = battleField->getFieldCell(currentPosition);

    Position2D nextPoint = currentPosition;

    if (action == MOVE_TOP) {
        nextPoint.y--;
        if (nextPoint.y < 0) {
            return false;
        }

        FieldCell& nextCell = battleField->getFieldCell(nextPoint);

        if (nextCell.isEmpty()) {
            nextCell.addUnit(unit);
            currentCell.deleteUnit();
            return true;
        }
    }
    else if (action == MOVE_LEFT) {
        nextPoint.x--;
        if (nextPoint.x < 0) {
            return false;
        }

        FieldCell& nextCell = battleField->getFieldCell(nextPoint);

        if (nextCell.isEmpty()) {
            nextCell.addUnit(unit);
            currentCell.deleteUnit();
            return true;
        }
    }
    else if (action == MOVE_RIGHT) {
        nextPoint.x++;
        if (nextPoint.x >= static_cast<int>(battleField->getWidth())) {
            return false;
        }

        FieldCell& nextCell = battleField->getFieldCell(nextPoint);

        if (nextCell.isEmpty()) {
            nextCell.addUnit(unit);
            currentCell.deleteUnit();
            return true;
        }
    }
    else if (action == MOVE_BOTTOM) {
        nextPoint.y++;
        if (nextPoint.y >= static_cast<int>(battleField->getHeight())) {
            return false;
        }

        FieldCell& nextCell = battleField->getFieldCell(nextPoint);

        if (nextCell.isEmpty()) {
            nextCell.addUnit(unit);
            currentCell.deleteUnit();
            return true;
        }
    }

    return false;
}
