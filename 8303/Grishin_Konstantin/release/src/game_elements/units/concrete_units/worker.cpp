#include "game_elements/units/concrete_units/worker.h"

#include <sstream>

Worker::Worker(Team team, const sf::Vector2i& pos, const UnitStats& stats):
    team(team), pos(pos), state(State::Stands), stats(stats), extraSteps(0)
{
    health = stats.maxHealth;
    steps = stats.maxSteps;
}


Entity* Worker::copy() const{
    auto e = new Worker(getTeam(), getPosition(), stats);

    e->setExtra(extraSteps);
    e->setHealth(health);
    e->setSteps(steps);

    if(target_x != -1 && target_y != -1)
        e->setTarget(target_x, target_y);

    return e;
}


void Worker::setPosition(int x, int y){
    pos.x = x;
    pos.y = y;
}


const sf::Vector2i& Worker::getPosition() const{
    return pos;
}


Team Worker::getTeam() const{
    return team;
}


bool Worker::delete_p() const{
    return toDelete;
}


void Worker::setActionState(){
    setWorkState();
}


void Worker::setTarget(int x, int y){
    state = State::Works;
    target_x = x;
    target_y = y;
}


sf::Vector2i Worker::getTarget() const
{
    return sf::Vector2i(target_x, target_y);
}


void Worker::move(int x, int y){
    setMoveState();
    setPosition(x, y);
}


bool Worker::isMovable() const{
    return (!moving && getHealth() > 0);
}


void Worker::setMoveState(){
    if(state == State::Works){
        target_x = -1;
        target_y = -1;
    }
    state = State::Moves;
    oldPosition = sf::Vector2f(getPosition());
    moving = 1;
}


void Worker::setWorkState(){
    if(state == State::Stands)
        state = State::Works;
    else if (state == State::Works){
        state = State::Stands;
        target_x = -1;
        target_y = -1;
    }
}


void Worker::constructAction(UnitAction &action) const{
    action.type = UnitAction::Work;
    if(target_x == -1 || target_y == -1)
        action.workAction.work = 0;
    else
        action.workAction.work = 1;
    action.workAction.x = target_x;
    action.workAction.y = target_y;
}


void Worker::update(float time){
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
            if(health <= 0) toDelete = 1;
        }
        break;

    case State::Works:
        break;

    default:
        timer = 0;
        break;
    }
}


sf::Vector2f Worker::getMovingOffset() const{
    if(state == State::Moves){
        sf::Vector2f offset(oldPosition - sf::Vector2f(getPosition()));
        offset -= sf::Vector2f(offset.x * timer/1500.f, offset.y * timer/1500.f);
        return offset;
    }
    return sf::Vector2f(0, 0);
}


void Worker::setHealth(float hp){
    health = hp;
    if(health > getMaxHealth()) health = getMaxHealth();
    if(health < 0) health = 0;
}


void Worker::setSteps(float steps){
    this->steps = steps;
    if(this->steps > getMaxSteps()) this->steps = getMaxSteps();
    if(this->steps < 0) this->steps = 0;
}


void Worker::setExtra(float extra){
    extraSteps = extra;
    if(extraSteps < 0) extraSteps = 0;
}


void Worker::damage(float dmg, const std::string&){
    health -= dmg;
    state = State::Damaged;
}


void Worker::heal(float hp){
    health += hp;
    if(health > stats.maxHealth) health = stats.maxHealth;
}


void Worker::increase(float val){
    steps += int(val);
    if(steps > getMaxSteps()) steps = getMaxSteps();
}


void Worker::resetSteps(){
    steps = stats.maxSteps;
}



float Worker::getHealth() const{
    return health;
}


float Worker::getMaxHealth() const{
    return stats.maxHealth;
}


float Worker::getSteps() const{
    return steps + extraSteps;
}


float Worker::getMaxSteps() const{
    return stats.maxSteps + extraSteps;
}


float Worker::getExtra() const
{
    return extraSteps;
}


Unit::Type Worker::getUnitType() const{
    return Unit::Worker;
}


std::string
Worker::getInfo() const{
    std::stringstream ss;

    ss << ((getTeam() == Team::Red)? "RED " : "BLU ")
       << "Worker" << std::endl;
    ss << "Health: " << getHealth() << "/" << getMaxHealth() << std::endl;
    ss << "Steps: " << getSteps() << "/" << getMaxSteps() << std::endl;
    ss << "With extra: " << extraSteps << std::endl;
    if(state == State::Works){
        ss << "Working on cell (" << target_x << "; " << target_y << ")" << std::endl;
    } else {
        ss << "Worker is free";
    }

    return ss.str();
}


const std::string& Worker::getID() const{
    return id;
}

