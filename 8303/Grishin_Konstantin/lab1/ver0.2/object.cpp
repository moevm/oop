#include "object.h"


#include "cell.h"
#include "cellgrid.h"

Object::Object(Cell *cell, Object::Type objType):
    objType(objType), cell(cell), bActive(0)
{
    cell->obj = this;
}


Object::Type Object::getObjectType() const{
    return objType;
}


void Object::setPosition(Cell *cell){
    if(this->cell)
        this->cell->obj = nullptr;
    cell->obj = this;
    this->cell = cell;
}


void Object::setActive(bool act){
    bActive = act;
}


void Object::setTeam(Team team){
    this->team = team;
}


Object::Team Object::getTeam() const{
    return team;
}


Point2i Object::getPos() const{
    return cell->getPoint();
}


Cell* Object::getCell() const{
    return cell;
}


bool Object::isActive() const{
    return bActive;
}
