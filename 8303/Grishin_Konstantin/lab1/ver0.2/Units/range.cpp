#include "Units/range.h"

#include <SFML/Graphics.hpp>

#include "weapon.h"
#include "cell.h"
#include "cellgrid.h"

Range::Range(Cell *cell,
             RangeWeapon *weapon,
             int iMaxHealth,
             int iMaxSteps,
             int iAttackRadius):
    Combat(cell, Combat::Range),
    iMaxHealth(iMaxHealth),
    iHealth(iMaxHealth),
    iMaxSteps(iMaxSteps),
    iSteps(iMaxSteps),
    iAttackRaduis(iAttackRadius)
{
    setMode(0);
    setWeapon(weapon);
}


void Range::setWeapon(RangeWeapon *weapon){
    Combat::setWeapon(weapon);
}


void Range::changeHealth(float iHealth){
    this->iHealth += iHealth;
    if(this->iHealth < 0) this->iHealth = 0;
    if(this->iHealth > iMaxHealth) this->iHealth = iMaxHealth;
}


void Range::changeSteps(float iSteps){
    this->iSteps += iSteps;
    if(this->iSteps < 0) this->iSteps = 0;
    if(this->iSteps > iMaxSteps) this->iSteps = iMaxSteps;
}


int Range::getAttackRadius() const{
    return iAttackRaduis;
}


float Range::health() const{
    return iHealth;
}


float Range::maxHealth() const{
    return iMaxHealth;
}


float Range::steps() const{
    return iSteps;
}


float Range::maxSteps() const{
    return iMaxSteps;
}


void Range::updateSteps(){
    iSteps = iMaxSteps;
}



//// ARCHER
Archer::Archer(Cell *cell, RangeWeapon *weapon):
    Range(cell, weapon, 14, 1, 3)
{}


void Archer::draw(sf::RenderTarget *target, int rect_size){
    sf::CircleShape shape(rect_size * 0.5f * 0.55f, 16);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((getPos().x + 0.5f) * rect_size, (getPos().y + 0.5f) * rect_size);

    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(0x80, 0x80, 0x80));

    target->draw(shape);
}


void Archer::move(Cell *dest){
    setMode(0);
    // play move animation
    // ...

    auto diff = dest->getPoint() - getPos();

    changeSteps(-(abs(diff.x) + abs(diff.y)));

    setPosition(dest);
}


void Archer::attack(Unit *enemy){
    if(getWeapon() != nullptr){
        enemy->damage(int(getWeapon()->fire(*enemy)));
    }
    else
    {
        enemy->damage(1);
    }
}


void Archer::damage(float dmg){
    changeHealth(-dmg);
}


void Archer::foothold(bool bMode){
    setMode(bMode);
}


void Archer::heal(float iAddHealth){
    changeHealth(iAddHealth);
}


Object* Archer::copy(CellGrid *field) const{
    RangeWeapon *weapon = nullptr;
    if(getWeapon() != nullptr){
        if(getWeapon()->getName() == "bow")
            weapon = new Bow();
    }
    return new Archer(field->getCell(this->getPos().x, this->getPos().y), weapon);
}


