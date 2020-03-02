#include "Units/melee.h"


#include <SFML/Graphics.hpp>

#include "weapon.h"
#include "cell.h"
#include "cellgrid.h"



Melee::Melee(Cell *cell,
             MeleeWeapon* weapon,
             int iMaxHealth,
             int iMaxSteps,
             int iBaseDamage):
    Combat(cell, Combat::Melee),
    iMaxHealth(iMaxHealth),
    iHealth(iMaxHealth),
    iMaxSteps(iMaxSteps),
    iSteps(iMaxSteps),
    iBaseDamage(iBaseDamage)
{
    setMode(0);
    setWeapon(weapon);
}


void Melee::changeHealth(float iHealth){
    this->iHealth += iHealth;
    if(this->iHealth < 0) this->iHealth = 0;
    if(this->iHealth > iMaxHealth) this->iHealth = iMaxHealth;
}


void Melee::changeSteps(float iSteps){
    this->iSteps += iSteps;
    if(this->iSteps < 0) this->iSteps = 0;
    if(this->iSteps > iMaxSteps) this->iSteps = iMaxSteps;
}


int Melee::getBaseDamage() const{
    return iBaseDamage;
}


void Melee::setWeapon(MeleeWeapon *wpn){
    // maybe do some weird things
    // ...

    Combat::setWeapon(wpn);
}


float Melee::health() const{
    return iHealth;
}


float Melee::maxHealth() const{
    return iMaxHealth;
}


float Melee::steps() const{
    return iSteps;
}


float Melee::maxSteps() const{
    return iMaxSteps;
}


void Melee::updateSteps(){
    iSteps = iMaxSteps;
}



Barbarian::Barbarian(Cell *cell, MeleeWeapon *weapon):
    Melee(cell, weapon, 18, 2, 9)
{}


void Barbarian::draw(sf::RenderTarget *target, int rect_size){
    sf::CircleShape shape(rect_size * 0.5f * 0.66f, 8);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((getPos().x + 0.5f) * rect_size, (getPos().y + 0.5f) * rect_size);

    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(0x80, 0x80, 0x80));

    target->draw(shape);
}


void Barbarian::move(Cell *dest){
    setMode(0);
    // play move animation
    // ...

    auto diff = dest->getPoint() - getPos();

    changeSteps(-(abs(diff.x) + abs(diff.y)));

    setPosition(dest);
}


void Barbarian::damage(float dmg){

    // Run getting damaged animation
    // ...

    changeHealth(-dmg);
}


void Barbarian::attack(Unit *enemy){
    if(getWeapon() != nullptr)
    {
        enemy->damage(int(getWeapon()->fire(*enemy)));
    }
    else
    {
        enemy->damage(getBaseDamage());
    }
}


void Barbarian::foothold(bool bMode){
    setMode(bMode);
}


void Barbarian::heal(float iAddHealth){
    changeHealth(iAddHealth);
}


Object* Barbarian::copy(CellGrid *field) const{
    MeleeWeapon *weapon = nullptr;
    if(getWeapon() != nullptr){
        if(getWeapon()->getName() == "club")
            weapon = new Club();
    }
    return new Barbarian(field->getCell(this->getPos().x, this->getPos().y), weapon);
}
