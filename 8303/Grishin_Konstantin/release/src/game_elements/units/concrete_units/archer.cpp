#include "game_elements/units/concrete_units/archer.h"

#include <sstream>

Archer::Archer(Team team, const sf::Vector2i& pos, const UnitStats &stats):
    Range(team, pos), state(State::Stands), stats(stats), extraDamage(0.f)
{
    health = stats.maxHealth;
    steps = stats.maxSteps;
}


Entity* Archer::copy() const{
    auto e = new Archer(getTeam(), getPosition(), stats);

    e->setExtra(extraDamage);
    e->setHealth(health);
    e->setSteps(steps);
    return e;

}


void Archer::setMoveState(){
    state = State::Moves;
    oldPosition = sf::Vector2f(getPosition());
    moving = 1;
}


void Archer::setAttackState(){
    state = State::Attacks;
}


void Archer::constructAction(UnitAction &action) const{
    action.type = UnitAction::Attack;
    action.attackAction.damage = stats.baseDamage;
    action.attackAction.radius = stats.attackRadius;
    action.attackAction.blind = stats.blindZone;
}


void Archer::update(float time){
    timer += time;
    switch(state){
    case State::Moves:
        if(timer > 1500){
            state = State::Stands;
            moving = 0;
        }
        break;

    case State::Damaged:
        if(timer > 1000){
            state = State::Stands;
            if(health <= 0){
                toDelete = 1;
            }
        }
        break;

    case State::Attacks:
        if(timer > 1000){
            state = State::Stands;
        }
        break;

    default:
        timer = 0;
        break;
    }
}


sf::Vector2f Archer::getMovingOffset() const{
    if(state == State::Moves){
        sf::Vector2f offset(oldPosition - sf::Vector2f(getPosition()));
        offset -= sf::Vector2f(offset.x * timer/1500.f, offset.y * timer/1500.f);
        return offset;
    }
    return sf::Vector2f(0, 0);
}


void Archer::setHealth(float hp){
    health = hp;
    if(health > getMaxHealth()) health = getMaxHealth();
    if(health < 0) health = 0;
}


void Archer::setSteps(float steps){
    this->steps = steps;
    if(this->steps > getMaxSteps()) this->steps = getMaxSteps();
    if(this->steps < 0) this->steps = 0;
}


void Archer::setExtra(float extra){
    extraDamage = extra;
    if(extraDamage < 0) extraDamage = 0;
}


void Archer::damage(float dmg, const std::string& dealer){
    if(dealer == "unit_knight")
        dmg *= 1.1f;
    health -= dmg;
    state = State::Damaged;
}


void Archer::heal(float hp){
    health += hp;
    if(health > stats.maxHealth) health = stats.maxHealth;
}


void Archer::increase(float val){
    extraDamage += val;
}


void Archer::resetSteps(){
    steps = stats.maxSteps;
}


float Archer::getHealth() const{
    return health;
}


float Archer::getMaxHealth() const{
    return stats.maxHealth;
}


float Archer::getSteps() const{
    return steps;
}


float Archer::getMaxSteps() const{
    return stats.maxSteps;
}


float Archer::getExtra() const
{
    return extraDamage;
}


std::string
Archer::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Archer" << std::endl;
    ss << "Health: " << getHealth() << "/" << getMaxHealth() << std::endl;
    ss << "Steps: " << getSteps() << "/" << getMaxSteps() << std::endl;
    ss << "Damage: " << stats.baseDamage << std::endl;
    ss << "With extra: " << extraDamage << std::endl;
    ss << "Attack radius: " << stats.attackRadius << std::endl;
    ss << "Blind zone: " << stats.blindZone;

    return ss.str();
}


const std::string& Archer::getID() const{
    return id;
}









