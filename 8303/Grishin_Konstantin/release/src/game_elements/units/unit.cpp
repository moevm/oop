#include "game_elements/units/unit.h"

UnitAction Unit::action() const{
    UnitAction action;
    constructAction(action);
    return action;
}
