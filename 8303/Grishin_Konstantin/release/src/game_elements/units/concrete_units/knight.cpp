#include "game_elements/units/concrete_units/knight.h"

#include <sstream>

Knight::Knight(Team team, const sf::Vector2i& pos, const UnitStats &stats):
    Melee(team, pos), state(State::Stands), stats(stats), extraDamage(0.f)
{
    health = stats.maxHealth;
    steps = stats.maxSteps;
}


Entity* Knight::copy() const{
    auto e = new Knight(getTeam(), getPosition(), stats);

    e->setExtra(extraDamage);
    e->setHealth(health);
    e->setSteps(steps);
    return e;
}


void Knight::setMoveState(){
    state = State::Moves;
    oldPosition = sf::Vector2f(getPosition());
    moving = 1;
}


void Knight::setAttackState(){
    state = State::Attacks;
}


void Knight::constructAction(UnitAction &action) const{
    action.type = UnitAction::Attack;
    action.attackAction.damage = stats.baseDamage;
    action.attackAction.radius = 0;
    action.attackAction.blind = 0;
}


void Knight::update(float time){
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


sf::Vector2f Knight::getMovingOffset() const{
    if(state == State::Moves){
        sf::Vector2f offset(oldPosition - sf::Vector2f(getPosition()));
        offset -= sf::Vector2f(offset.x * timer/1500.f, offset.y * timer/1500.f);
        return offset;
    }
    return sf::Vector2f(0, 0);
}


void Knight::setHealth(float hp){
    health = hp;
    if(health > getMaxHealth()) health = getMaxHealth();
    if(health < 0) health = 0;
}


void Knight::setSteps(float steps){
    this->steps = steps;
    if(this->steps > getMaxSteps()) this->steps = getMaxSteps();
    if(this->steps < 0) this->steps = 0;
}


void Knight::setExtra(float extra){
    extraDamage = extra;
    if(extraDamage < 0) extraDamage = 0;
}


void Knight::damage(float dmg, const std::string &dealer){
    if(dealer == "unit_troll"){
        dmg *= 1.1f;
    }

    health -= dmg;
}


void Knight::heal(float hp){
    health += hp;
    if(health > stats.maxHealth) health = stats.maxHealth;
}


void Knight::increase(float val){
    extraDamage += val;
}


void Knight::resetSteps(){
    steps = stats.maxSteps;
}


float Knight::getHealth() const{
    return health;
}


float Knight::getMaxHealth() const{
    return stats.maxHealth;
}


float Knight::getSteps() const{
    return steps;
}


float Knight::getMaxSteps() const{
    return stats.maxSteps;
}


float Knight::getExtra() const
{
    return extraDamage;
}


std::string
Knight::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Knight" << std::endl;
    ss << "Health: " << getHealth() << "/" << getMaxHealth() << std::endl;
    ss << "Steps: " << getSteps() << "/" << getMaxSteps() << std::endl;
    ss << "With extra: " << extraDamage << std::endl;
    ss << "Damage: " << stats.baseDamage;

    return ss.str();
}


const std::string& Knight::getID() const{
    return id;
}
