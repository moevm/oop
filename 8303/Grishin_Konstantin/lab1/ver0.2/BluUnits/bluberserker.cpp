#include "bluberserker.h"

#include <SFML/Graphics.hpp>

#include "cell.h"
#include "cellgrid.h"
#include "weapon.h"

BluBerserker::BluBerserker(Cell *cell, NukerWeapon *weapon):
    Berserker(cell, weapon)
{
    setTeam(Object::Team::Blu);
}


void BluBerserker::draw(sf::RenderTarget *target, int rect_size){
    sf::CircleShape shape(rect_size * 0.5f * 0.7f, 4);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((getPos().x + 0.5f) * rect_size, (getPos().y + 0.5f) * rect_size);

    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(0x20, 0x80, 0xC4));

    target->draw(shape);
}


Object* BluBerserker::copy(CellGrid *field) const{
    NukerWeapon *weapon = nullptr;
    if(getWeapon() != nullptr){
        if(getWeapon()->getName() == "scythe")
            weapon = new Scythe();
    }
    return new BluBerserker(field->getCell(this->getPos().x, this->getPos().y), weapon);
}
