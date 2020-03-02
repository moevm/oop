#include "blubarbarian.h"

#include <SFML/Graphics.hpp>

#include "cell.h"
#include "cellgrid.h"
#include "weapon.h"

BluBarbarian::BluBarbarian(Cell *cell, MeleeWeapon *weapon):
    Barbarian(cell, weapon)
{
    setTeam(Object::Team::Blu);
}


void BluBarbarian::draw(sf::RenderTarget *target, int rect_size){
    sf::CircleShape shape(rect_size * 0.5f * 0.66f, 8);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((getPos().x + 0.5f) * rect_size, (getPos().y + 0.5f) * rect_size);

    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(0x20, 0x80, 0xC4));

    target->draw(shape);
}


Object* BluBarbarian::copy(CellGrid *field) const{
    MeleeWeapon *weapon = nullptr;
    if(getWeapon() != nullptr){
        if(getWeapon()->getName() == "club")
            weapon = new Club();
    }
    return new BluBarbarian(field->getCell(this->getPos().x, this->getPos().y), weapon);
}
