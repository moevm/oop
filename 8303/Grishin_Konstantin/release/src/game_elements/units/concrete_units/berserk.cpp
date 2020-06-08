#include "game_elements/units/concrete_units/berserk.h"

#include <sstream>

Berserk::Berserk(Team team, const sf::Vector2i& pos, const UnitStats &stats):
    Nuker(team, pos), state(State::Stands), stats(stats), extraDamage(0.f)
{
    health = stats.maxHealth;
    steps = stats.maxSteps;
}


Entity* Berserk::copy() const{
    auto e = new Berserk(getTeam(), getPosition(), stats);

    e->setExtra(extraDamage);
    e->setHealth(health);
    e->setSteps(steps);
    return e;
}


void Berserk::setMoveState(){
    state = State::Moves;
    oldPosition = sf::Vector2f(getPosition());
    moving = 1;
}


void Berserk::setAttackState(){
    state = State::Attacks;
}


void Berserk::constructAction(UnitAction &action) const{
    action.type = UnitAction::Attack;
    action.attackAction.damage = stats.baseDamage;
    action.attackAction.radius = stats.attackRadius;
    action.attackAction.blind = 0;
}


void Berserk::update(float time){
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


sf::Vector2f Berserk::getMovingOffset() const{
    if(state == State::Moves){
        sf::Vector2f offset(oldPosition - sf::Vector2f(getPosition()));
        offset -= sf::Vector2f(offset.x * timer/1500.f, offset.y * timer/1500.f);
        return offset;
    }
    return sf::Vector2f(0, 0);
}


void Berserk::setHealth(float hp){
    health = hp;
    if(health > getMaxHealth()) health = getMaxHealth();
    if(health < 0) health = 0;
}


void Berserk::setSteps(float steps){
    this->steps = steps;
    if(this->steps > getMaxSteps()) this->steps = getMaxSteps();
    if(this->steps < 0) this->steps = 0;
}


void Berserk::setExtra(float extra){
    extraDamage = extra;
    if(extraDamage < 0) extraDamage = 0;
}


void Berserk::damage(float dmg, const std::string &dealer){
    if(dealer == "unit_wizard"){
        dmg *= 1.4f;
    }

    health -= dmg;
}


void Berserk::heal(float hp){
    health += hp;
    if(health > stats.maxHealth) health = stats.maxHealth;
}


void Berserk::increase(float val){
    extraDamage += val;
}


void Berserk::resetSteps(){
    steps = stats.maxSteps;
}


float Berserk::getHealth() const{
    return health;
}


float Berserk::getMaxHealth() const{
    return stats.maxHealth;
}


float Berserk::getSteps() const{
    return steps;
}


float Berserk::getMaxSteps() const{
    return stats.maxSteps;
}


float Berserk::getExtra() const
{
    return extraDamage;
}


std::string
Berserk::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Berserk" << std::endl;
    ss << "Health: " << getHealth() << "/" << getMaxHealth() << std::endl;
    ss << "Steps: " << getSteps() << "/" << getMaxSteps() << std::endl;
    ss << "Damage: " << stats.baseDamage << std::endl;
    ss << "With extra: " << extraDamage << std::endl;
    ss << "Attack radius: " << stats.attackRadius;

    return ss.str();
}


const std::string& Berserk::getID() const{
    return id;
}



