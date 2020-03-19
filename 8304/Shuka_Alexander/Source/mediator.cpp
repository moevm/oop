#include "mediator.h"
#include "Unit/unit.h"
#include "Field/gamefield.h"

using namespace unit;


Mediator::Mediator(std::shared_ptr<GameField> gameField)
{
    this->gameField = gameField;
}


bool Mediator::notify(std::shared_ptr<Unit> unit,
                      const std::string& act)
{
    Point2D currentPoint = unit->getPosition();
    auto currentCell = gameField->getCell(currentPoint);
    Point2D nextPoint = currentPoint;

    if (act == MOVE_TOP || act == MOVE_LEFT ||
            act == MOVE_RIGHT || act == MOVE_BOTTOM) {
        if (act == MOVE_TOP) {
            nextPoint.y--;
            if (nextPoint.y < 0) {
                return false;
            }
        }
        else if (act == MOVE_LEFT) {
            nextPoint.x--;
            if (nextPoint.x < 0) {
                return false;
            }
        }
        else if (act == MOVE_RIGHT) {
            nextPoint.x++;
            if (nextPoint.x >= static_cast<int>(gameField->getWidth())) {
                return false;
            }

        }
        else if (act == MOVE_BOTTOM) {
            nextPoint.y++;
            if (nextPoint.y >= static_cast<int>(gameField->getHeight())) {
                return false;
            }
        }

        auto nextCell = gameField->getCell(nextPoint);

        if (nextCell->isEmpty() && nextCell->getLandscape()->canMove(unit)) {
            nextCell->addUnit(unit);
            nextCell->getLandscape()->hurtUnit(unit);
            currentCell->deleteUnit();
            (*nextCell->getNeutralObject())[unit];
            nextCell->deleteNeutralObject();
            return true;
        }
    }
    else if (act == CRT_UNIT) {
        if (currentCell->isEmpty()) {
            currentCell->addUnit(unit);
            return true;
        }
    }

    return false;
}
