#include "mediator.hpp"
#include "BattleField.hpp"
#include "unit.hpp"
#include "poisonobject.hpp"

Mediator::Mediator(std::shared_ptr<BattleField> battleField)
{
    this->battleField = battleField;
}


bool Mediator::notify(std::shared_ptr<Unit> unit,const std::string& action)
{
    Position2D currentPosition = unit->getPosition();
    FieldCell& currentCell = battleField->getFieldCell(currentPosition);
    Position2D nextPoint = currentPosition;

    if(action == MOVE_TOP || action == MOVE_LEFT ||
    action == MOVE_RIGHT || action == MOVE_BOTTOM){
        if (action == MOVE_TOP) {
            nextPoint.y--;
            if (nextPoint.y < 0) {
                return false;
            }
        }
        else if (action == MOVE_LEFT) {
            nextPoint.x--;
            if (nextPoint.x < 0) {
                return false;
            }
        }
        else if (action == MOVE_RIGHT) {
            nextPoint.x++;
            if (nextPoint.x >= static_cast<int>(battleField->getWidth())) {
                return false;
            }
        }
        else if (action == MOVE_BOTTOM) {
            nextPoint.y++;
            if (nextPoint.y >= static_cast<int>(battleField->getHeight())) {
                return false;
            }
        }
        
        FieldCell& nextCell = battleField->getFieldCell(nextPoint);
                
        if (nextCell.isEmpty() && nextCell.getLandscape()->canMove(unit)) {
            nextCell.addUnit(unit);
            nextCell.getLandscape()->hurtUnit(unit);
            currentCell.deleteUnit();
            (*nextCell.getNeutralObject())[unit];
            nextCell.deleteNeutralObject();
            return true;
        }
        
    }else if (action == CREATE_UNIT){
        if (currentCell.isEmpty()) {
            currentCell.addUnit(unit);
            return true;
        }
    }
    return false;
}
