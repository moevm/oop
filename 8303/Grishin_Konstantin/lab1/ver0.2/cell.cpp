#include "cell.h"
#include <SFML/Graphics.hpp>

#include "point.h"
#include "object.h"

Cell::Cell(Type type, float iMoveModifier, float fDamageModifier):
    type(type), iMoveModifier(iMoveModifier), fDamageModifier(fDamageModifier)
{
    obj = nullptr;
}


float Cell::getMoveModifier() const{
    return iMoveModifier;
}


void Cell::setObject(Object *object){
    if(obj)
        return;

    this->obj = object;
    object->cell = this;
}


Object* Cell::getObject() const{
    return obj;
}


Object* Cell::pullObject(){
    auto toRet = obj;
    obj = nullptr;
    return toRet;
}


Point2i Cell::getPoint() const{
    return coords;
}


Cell::Type Cell::getType() const{
    return type;
}


PCell::PCell():
    Cell(Cell::Type::Open, 1, 1)
{
}


void PCell::draw(sf::RenderTarget *target, const Point2i &point, int iSize){
    sf::RectangleShape cell_shape(sf::Vector2f(iSize-4, iSize-4));
    cell_shape.setOrigin(-2, -2);
    cell_shape.setOutlineThickness(2);
    cell_shape.setOutlineColor(sf::Color(0x44, 0x30, 0x1f, 0xFF));
    cell_shape.setFillColor(sf::Color(0x00, 0xFF, 0x00, 0xFF));
    cell_shape.setPosition(point.x, point.y);

    target->draw(cell_shape);
}
