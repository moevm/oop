#include "game_elements/units/concrete_units/wizard.h"

#include <sstream>

Wizard::Wizard(Team team, const sf::Vector2i& pos, const UnitStats& stats):
    Nuker(team, pos), state(State::Stands), stats(stats), extraDamage(0.f)
{
    health = stats.maxHealth;
    steps = stats.maxSteps;
}


Entity* Wizard::copy() const{
    auto e = new Wizard(getTeam(), getPosition(), stats);

    e->setExtra(extraDamage);
    e->setHealth(health);
    e->setSteps(steps);
    return e;
}


void Wizard::setMoveState(){
    state = State::Moves;
    oldPosition = sf::Vector2f(getPosition());
    moving = 1;
}


void Wizard::setAttackState(){
    state = State::Attacks;
}


void Wizard::constructAction(UnitAction &action) const{
    action.type = UnitAction::Attack;
    action.attackAction.damage = stats.baseDamage;
    action.attackAction.radius = stats.attackRadius;
    action.attackAction.blind = 0;
}


void Wizard::update(float time){
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


sf::Vector2f Wizard::getMovingOffset() const{
    if(state == State::Moves){
        sf::Vector2f offset(oldPosition - sf::Vector2f(getPosition()));
        offset -= sf::Vector2f(offset.x * timer/1500.f, offset.y * timer/1500.f);
        return offset;
    }
    return sf::Vector2f(0, 0);
}


void Wizard::setHealth(float hp){
    health = hp;
    if(health > getMaxHealth()) health = getMaxHealth();
    if(health < 0) health = 0;
}


void Wizard::setSteps(float steps){
    this->steps = steps;
    if(this->steps > getMaxSteps()) this->steps = getMaxSteps();
    if(this->steps < 0) this->steps = 0;
}


void Wizard::setExtra(float extra){
    extraDamage = extra;
    if(extraDamage < 0) extraDamage = 0;
}


void Wizard::damage(float dmg, const std::string &dealer){
    if(dealer == "unit_archer"){
        dmg *= 1.2f;
    }

    health -= dmg;
}


void Wizard::heal(float hp){
    health += hp;
    if(health > stats.maxHealth) health = stats.maxHealth;
}


void Wizard::increase(float val){
    extraDamage += val;
}


void Wizard::resetSteps(){
    steps = stats.maxSteps;
}



float Wizard::getHealth() const{
    return health;
}


float Wizard::getMaxHealth() const{
    return stats.maxHealth;
}


float Wizard::getSteps() const{
    return steps;
}


float Wizard::getMaxSteps() const{
    return stats.maxSteps;
}


float Wizard::getExtra() const
{
    return extraDamage;
}


std::string
Wizard::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Wizard" << std::endl;
    ss << "Health: " << getHealth() << "/" << getMaxHealth() << std::endl;
    ss << "Steps: " << getSteps() << "/" << getMaxSteps() << std::endl;
    ss << "Damage: " << stats.baseDamage << std::endl;
    ss << "With extra: " << extraDamage << std::endl;
    ss << "Attack radius: " << stats.attackRadius;

    return ss.str();
}


const std::string& Wizard::getID() const{
    return id;
}

