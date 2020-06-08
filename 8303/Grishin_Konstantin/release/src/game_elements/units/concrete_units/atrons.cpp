#include "game_elements/units/concrete_units/atrons.h"

#include <sstream>

Atrons::Atrons(Team team, const sf::Vector2i& pos, const UnitStats &stats):
    Range(team, pos), state(State::Stands), stats(stats), extraDamage(0.f)
{
    health = stats.maxHealth;
    steps = stats.maxSteps;
}


Entity* Atrons::copy() const{
    auto e = new Atrons(getTeam(), getPosition(), stats);

    e->setExtra(extraDamage);
    e->setHealth(health);
    e->setSteps(steps);
    return e;
}


void Atrons::setMoveState(){
    state = State::Moves;
    oldPosition = sf::Vector2f(getPosition());
    moving = 1;
}


void Atrons::setAttackState(){
    state = State::Attacks;
}


void Atrons::constructAction(UnitAction &action) const{
    action.type = UnitAction::Attack;
    action.attackAction.damage = stats.baseDamage;
    action.attackAction.radius = stats.attackRadius;
    action.attackAction.blind = stats.blindZone;
}


void Atrons::update(float time){
    timer += time;
    switch(state){
    case State::Moves:
        if(timer > 800){
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


sf::Vector2f Atrons::getMovingOffset() const{
    if(state == State::Moves){
        sf::Vector2f offset_3rd(oldPosition - sf::Vector2f(getPosition()));
        offset_3rd = sf::Vector2f(offset_3rd.x/3.f, offset_3rd.y/3.f);
        sf::Vector2f offset = offset_3rd - sf::Vector2f(offset_3rd.x * timer/400.f, offset_3rd.y * timer/400.f);

        offset += offset_3rd;
        if(timer < 400){
            offset += offset_3rd;
        }
        return offset;
    }
}


void Atrons::setHealth(float hp){
    health = hp;
    if(health > getMaxHealth()) health = getMaxHealth();
    if(health < 0) health = 0;
}


void Atrons::setSteps(float steps){
    this->steps = steps;
    if(this->steps > getMaxSteps()) this->steps = getMaxSteps();
    if(this->steps < 0) this->steps = 0;
}


void Atrons::setExtra(float extra){
    extraDamage = extra;
    if(extraDamage < 0) extraDamage = 0;
}


void Atrons::damage(float dmg, const std::string &dealer){
    if(dealer == "unit_atrons"){
        dmg *= 1.8f;
    }

    health -= dmg;
}


void Atrons::heal(float hp){
    health += hp;
    if(health > stats.maxHealth) health = stats.maxHealth;
}


void Atrons::increase(float val){
    extraDamage += val;
}


void Atrons::resetSteps(){
    steps = stats.maxSteps;
}


float Atrons::getHealth() const{
    return health;
}


float Atrons::getMaxHealth() const{
    return stats.maxHealth;
}


float Atrons::getSteps() const{
    return steps;
}


float Atrons::getMaxSteps() const{
    return stats.maxSteps;
}


float Atrons::getExtra() const
{
    return extraDamage;
}


std::string
Atrons::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Atrons" << std::endl;
    ss << "Health: " << getHealth() << "/" << getMaxHealth() << std::endl;
    ss << "Steps: " << getSteps() << "/" << getMaxSteps() << std::endl;
    ss << "Damage: " << stats.baseDamage << std::endl;
    ss << "With extra: " << extraDamage << std::endl;
    ss << "Attack radius: " << stats.attackRadius << std::endl;
    ss << "Blind zone: " << stats.blindZone;

    return ss.str();
}


const std::string& Atrons::getID() const{
    return id;
}
