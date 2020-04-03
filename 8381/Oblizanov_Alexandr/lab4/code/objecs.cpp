#include "objects.h"


Unit::Unit(Unit &unit)
    :name(unit.name), movable(unit.movable), attackSkills(unit.attackSkills),
      securitySkills(unit.securitySkills), characteristics(unit.characteristics),
      moveMediator(nullptr) {}

std::string Unit::about() {
    std::string output;
    output += this->name + "\nCharacteristics:\n";
    output += "Move: " + std::to_string(characteristics.getMove()) + "\nPower: " + std::to_string(characteristics.getPower()) + "\nSpread: " + std::to_string(characteristics.getSpread()) + "\nBonus: " + std::to_string(characteristics.getBonus()) + "\n";
    output += "Attack skills:\n";
    output += "Move: " + std::to_string(attackSkills.getMove()) + "\nPower: " + std::to_string(attackSkills.getPower()) + "\nSpread: " + std::to_string(attackSkills.getSpread()) + "\nBonus: " + std::to_string(attackSkills.getBonus()) + "\n";
    output += "Security skills:\n";
    output += "Move: " + std::to_string(securitySkills.getMove()) + "\nPower: " + std::to_string(securitySkills.getPower()) + "\nSpread: " + std::to_string(securitySkills.getSpread()) + "\nBonus: " + std::to_string(securitySkills.getBonus()) + "\n";
    return output;
}

SimpleCyberScientist::SimpleCyberScientist(IBaseObserver *base)
{
    name = "Simple cyber scientist";
    baseNumber = base->getNumber();
    attackSkills.setAll(10,20,30,0);
    securitySkills.setAll(10,20,20,0);
    characteristics.setAll(150,100,0,0);
    moveMediator = nullptr;
    baseObserver = base;
}

AttackCyberScientist::AttackCyberScientist(IBaseObserver *base) {
    name = "Attack cyber scientist";
    baseNumber = base->getNumber();
    attackSkills.setAll(30,50,70,0);
    securitySkills.setAll(30,50,50,0);
    characteristics.setAll(150,200,0,0);
    baseObserver = base;
}
SupportCyberScientist::SupportCyberScientist(IBaseObserver *base) {
    name = "Support cyber scientist";
    baseNumber = base->getNumber();
    attackSkills.setAll(10,20,30,0);
    securitySkills.setAll(50,70,70,0);
    characteristics.setAll(200,150,0,0);
    baseObserver = base;
}

SimpleCyberBerserk::SimpleCyberBerserk(IBaseObserver *base) {
    name = "Simple cyber berserk";
    baseNumber = base->getNumber();
    attackSkills.setAll(40,40,10,0);
    securitySkills.setAll(30,0,0,0);
    characteristics.setAll(100,150,0,0);
    baseObserver = base;
}

AttackCyberBerserk::AttackCyberBerserk(IBaseObserver *base) {
    name = "Attack cyber berserk";
    baseNumber = base->getNumber();
    attackSkills.setAll(80,80,50,0);
    securitySkills.setAll(50,10,10,0);
    characteristics.setAll(100,250,0,0);
    baseObserver = base;
}

SupportCyberBerserk::SupportCyberBerserk(IBaseObserver *base) {
    name = "Support cyber berserk";
    baseNumber = base->getNumber();
    attackSkills.setAll(40,40,30,0);
    securitySkills.setAll(80,40,40,0);
    characteristics.setAll(150,200,0,0);
    baseObserver = base;
}

void Unit::move(int x, int y)
{
    moveMediator->Notify(this, x, y);
}

IUnit &Unit::operator+=(FieldItem *item)
{
    if (item != nullptr)
        item->unitInfluence(this);
    return *this;
}

//GETTERS/SETTERS

Skills Unit::getAttackSkills() const
{
    return attackSkills;
}

Skills Unit::getSecuritySkills() const
{
    return securitySkills;
}


Skills Unit::getCharacteristics() const
{
    return characteristics;
}

void Unit::setAttackBonus(int bonus)
{
    attackSkills.setBonus(bonus);
}

void Unit::setSecurityBonus(int bonus)
{
    securitySkills.setBonus(bonus);
}

void Unit::setCharacteristicsBonus(int bonus)
{
    characteristics.setBonus(bonus);
}

void Unit::setMoveMediator(MoveMediator *value)
{
    moveMediator = value;
}

unsigned Unit::getBaseNumber() const
{
return baseNumber;
}

void Unit::setAttackMediator(IAttackMediator *value)
{
    attackMediator = value;
}

bool Unit::receiveAttack(IUnit *unit)
{
    Skills att = unit->getAttackSkills();
    int attMove = att.getMove() + att.getBonus() - (securitySkills.getMove() + securitySkills.getBonus());
    int attPower = att.getPower() + att.getBonus() - (securitySkills.getPower() + securitySkills.getBonus());
    int attSpread = att.getSpread() + att.getBonus() - (securitySkills.getSpread() + securitySkills.getBonus());
    if (attMove > 0)
    {
        securitySkills.setBonus(0);
        characteristics.reduceMove(attMove);
    }
    if (attPower > 0)
    {
        securitySkills.setBonus(0);
        characteristics.reducePower(attPower);
    }
    if (attSpread > 0)
    {
        securitySkills.setBonus(0);
        characteristics.reduceSpread(attSpread);
    }
    if (characteristics.getMove() == 0)
        movable = false;
    if (characteristics.getPower() == 0)
        return false;
    return true;
}

bool Unit::attack(int x, int y)
{
    return attackMediator->attack(this, x, y);
}
