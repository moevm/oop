#include "Unit.h"

Unit::Unit() {
    x = 0;
    y = 0;
    health = 0;
    stats = Attributes();
}

int Unit::getX(){
    return this->x;
}

int Unit::getY(){
    return this->y;
}

Attributes Unit::getStats(){
    return this->stats;
}

int Unit::getHealth(){
    return this->health;
}
char Unit::getSymbol() {
    return this->getStats().getSymbol();
}

void Unit::setStats(Attributes stats) {
    this->stats = stats;
}

void Unit::setHealth(int health){
    if(health >= 0)
        this->health = health;
}
void Unit::setX(int x){
    if(x >= 0)
        this->x = x;
}
void Unit::setY(int y){
    if(y >= 0)
        this->y = y;
}

void Unit::setDistance(int distance){
    if(distance > 0)
        this->stats.setDistance(distance);

}
void Unit::setSpeed(int speed){
    if(speed > 0)
        this->stats.setSpeed(speed);
}
void Unit::setSymbol(char symbol){
    this->stats.setSymbol(symbol);
}
void Unit::setArmour(std::string armour){
    this->stats.setArmour(armour);
}
void Unit::setDamage(std::string damage){
    this->stats.setDamage(damage);
}