#include "bluarcher.h"

#include "SFML/Graphics.hpp"

#include "cell.h"
#include "cellgrid.h"
#include "weapon.h"

BluArcher::BluArcher(Cell *cell, RangeWeapon *weapon):
    Archer(cell, weapon)
{
    setTeam(Object::Team::Blu);
}


void BluArcher::draw(sf::RenderTarget *target, int rect_size){
    sf::CircleShape shape(rect_size * 0.5f * 0.55f, 16);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((getPos().x + 0.5f) * rect_size, (getPos().y + 0.5f) * rect_size);

    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(0x20, 0x80, 0xC4));

    target->draw(shape);
}


Object* BluArcher::copy(CellGrid *field) const{
    RangeWeapon *weapon = nullptr;
    if(getWeapon() != nullptr){
        if(getWeapon()->getName() == "bow")
            weapon = new Bow();
    }
    return new BluArcher(field->getCell(this->getPos().x, this->getPos().y), weapon);
}
