#include "redberserker.h"

#include <SFML/Graphics.hpp>

#include "cell.h"
#include "cellgrid.h"
#include "weapon.h"

RedBerserker::RedBerserker(Cell *cell, NukerWeapon *weapon):
    Berserker(cell, weapon)
{
    setTeam(Object::Team::Red);
}


void RedBerserker::draw(sf::RenderTarget *target, int rect_size){
    sf::CircleShape shape(rect_size * 0.5f * 0.7f, 4);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((getPos().x + 0.5f) * rect_size, (getPos().y + 0.5f) * rect_size);

    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(0xC4, 0x40, 0x20));

    target->draw(shape);
}


Object* RedBerserker::copy(CellGrid *field) const{
    NukerWeapon *weapon = nullptr;
    if(getWeapon() != nullptr){
        if(getWeapon()->getName() == "scythe")
            weapon = new Scythe();
    }
    return new RedBerserker(field->getCell(this->getPos().x, this->getPos().y), weapon);
}
