#include "redbarbarian.h"

#include <SFML/Graphics.hpp>

#include "cell.h"
#include "cellgrid.h"
#include "weapon.h"

RedBarbarian::RedBarbarian(Cell *cell, MeleeWeapon *weapon):
    Barbarian(cell, weapon)
{
    setTeam(Object::Team::Red);
}


void RedBarbarian::draw(sf::RenderTarget *target, int rect_size){
    sf::CircleShape shape(rect_size * 0.5f * 0.66f, 8);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((getPos().x + 0.5f) * rect_size, (getPos().y + 0.5f) * rect_size);

    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(0xC4, 0x40, 0x20));

    target->draw(shape);
}


Object* RedBarbarian::copy(CellGrid *field) const{
    MeleeWeapon *weapon = nullptr;
    if(getWeapon() != nullptr){
        if(getWeapon()->getName() == "club")
            weapon = new Club();
    }
    return new RedBarbarian(field->getCell(this->getPos().x, this->getPos().y), weapon);
}
