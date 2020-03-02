#include "Units/nuker.h"


#include <SFML/Graphics.hpp>

#include "weapon.h"
#include "cell.h"
#include "cellgrid.h"

Nuker::Nuker(Cell *cell,
             NukerWeapon *weapon,
             int iMaxHealth,
             int iMaxSteps,
             int iBaseDamage,
             int iAttackRadius):
    Combat(cell, Combat::Nuker),
    iMaxHealth(iMaxHealth),
    iHealth(iMaxHealth),
    iMaxSteps(iMaxSteps),
    iSteps(iMaxSteps),
    iBaseDamage(iBaseDamage),
    iAttackRadius(iAttackRadius)
{
    setMode(0);
    setWeapon(weapon);
}


void Nuker::setWeapon(NukerWeapon *weapon){
    Combat::setWeapon(weapon);
}


void Nuker::changeHealth(float iHealth){
    this->iHealth += iHealth;
    if(this->iHealth < 0) this->iHealth = 0;
    if(this->iHealth > iMaxHealth) this->iHealth = iMaxHealth;
}


void Nuker::changeSteps(float iSteps){
    this->iSteps += iSteps;
    if(this->iSteps < 0) this->iSteps = 0;
    if(this->iSteps > iMaxSteps) this->iSteps = iMaxSteps;
}


int Nuker::getAttackRadius() const{
    return iAttackRadius;
}


float Nuker::getBaseDamage() const{
    return iBaseDamage;
}


float Nuker::health() const{
    return iHealth;
}


float Nuker::maxHealth() const{
    return iMaxHealth;
}


float Nuker::steps() const{
    return iSteps;
}


float Nuker::maxSteps() const{
    return iMaxSteps;
}


void Nuker::updateSteps(){
    iSteps = iMaxSteps;
}



//// BERSERKER
Berserker::Berserker(Cell *cell, NukerWeapon *weapon):
    Nuker(cell, weapon, 15, 2, 5, 1)
{}


void Berserker::draw(sf::RenderTarget *target, int rect_size){
    sf::CircleShape shape(rect_size * 0.5f * 0.7f, 4);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition((getPos().x + 0.5f) * rect_size, (getPos().y + 0.5f) * rect_size);

    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(0x80, 0x80, 0x80));

    target->draw(shape);
}


void Berserker::move(Cell *dest){
    setMode(0);
    // play move animation
    // ...

    auto diff = dest->getPoint() - getPos();

    changeSteps(-(abs(diff.x) + abs(diff.y)));

    setPosition(dest);
}


void Berserker::attack(Unit *enemy){
    if(getWeapon() != nullptr)
    {
        enemy->damage(int(getWeapon()->fire(*enemy)));
    }
    else
    {
        enemy->damage(getBaseDamage());
    }
}


void Berserker::damage(float dmg){
    changeHealth(-dmg);
}


void Berserker::heal(float iAddHealth){
    changeHealth(iAddHealth);
}


void Berserker::foothold(bool bMode){
    setMode(bMode);
}


Object* Berserker::copy(CellGrid *field) const{
    NukerWeapon *weapon = nullptr;
    if(getWeapon() != nullptr){
        if(getWeapon()->getName() == "scythe")
            weapon = new Scythe();
    }
    return new Berserker(field->getCell(this->getPos().x, this->getPos().y), weapon);
}













