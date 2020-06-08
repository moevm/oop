#include "game_elements/units/concrete_units/troll.h"

#include <sstream>

Troll::Troll(Team team, const sf::Vector2i& pos, const UnitStats &stats):
    Melee(team, pos), state(State::Stands), stats(stats), extraDamage(0.f)
{
    health = stats.maxHealth;
    steps = stats.maxSteps;
}


Entity* Troll::copy() const{
    auto e = new Troll(getTeam(), getPosition(), stats);

    e->setExtra(extraDamage);
    e->setHealth(health);
    e->setSteps(steps);
    return e;
}


void Troll::setMoveState(){
    state = State::Moves;
    oldPosition = sf::Vector2f(getPosition());
    moving = 1;
}


void Troll::setAttackState(){
    state = State::Attacks;
}


void Troll::constructAction(UnitAction &action) const{
    action.type = UnitAction::Attack;
    action.attackAction.damage = stats.baseDamage;
    action.attackAction.radius = 0;
    action.attackAction.blind = 0;
}


void Troll::update(float time){
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


sf::Vector2f Troll::getMovingOffset() const{
    if(state == State::Moves){
        sf::Vector2f offset(oldPosition - sf::Vector2f(getPosition()));
        offset -= sf::Vector2f(offset.x * timer/1500.f, offset.y * timer/1500.f);
        return offset;
    }
    return sf::Vector2f(0, 0);
}


void Troll::setHealth(float hp){
    health = hp;
    if(health > getMaxHealth()) health = getMaxHealth();
    if(health < 0) health = 0;
}


void Troll::setSteps(float steps){
    this->steps = steps;
    if(this->steps > getMaxSteps()) this->steps = getMaxSteps();
    if(this->steps < 0) this->steps = 0;
}


void Troll::setExtra(float extra){
    extraDamage = extra;
    if(extraDamage < 0) extraDamage = 0;
}


void Troll::damage(float dmg, const std::string &dealer){
    if(dealer == "unit_troll"){
        dmg *= 0.8f;
    }

    health -= dmg;
}


void Troll::heal(float hp){
    health += hp;
    if(health > stats.maxHealth) health = stats.maxHealth;
}


void Troll::increase(float val){
    extraDamage += val;
}


void Troll::resetSteps(){
    steps = stats.maxSteps;
}



float Troll::getHealth() const{
    return health;
}


float Troll::getMaxHealth() const{
    return stats.maxHealth;
}


float Troll::getSteps() const{
    return steps;
}


float Troll::getMaxSteps() const{
    return stats.maxSteps;
}


float Troll::getExtra() const
{
    return extraDamage;
}


std::string
Troll::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Troll" << std::endl;
    ss << "Health: " << getHealth() << "/" << getMaxHealth() << std::endl;
    ss << "Steps: " << getSteps() << "/" << getMaxSteps() << std::endl;
    ss << "Damage: " << stats.baseDamage << std::endl;
    ss << "With extra: " << extraDamage;

    return ss.str();
}


const std::string& Troll::getID() const{
    return id;
}

