//
// Created by anton on 02.03.2020.
//

#include "Attributes.h"

int Attributes::getDistance(){
    return this->distance;
}

int Attributes::getSpeed(){
    return this->speed;
}

char Attributes::getSymbol(){
    return this->symbol;
}

Armour* Attributes::getArmour(){
    return this->armour;
}

Damage* Attributes::getDamage(){
    return this->damage;
}

void Attributes::setDistance(int distance){
    if(distance > 0)
        this->distance = distance;

}
void Attributes::setSpeed(int speed){
    if(speed > 0)
        this->speed = speed;
}
void Attributes::setSymbol(char symbol){
    this->symbol = symbol;
}
void Attributes::setArmour(std::string armour){
    this->armour->set_type(armour);
}
void Attributes::setDamage(std::string damage){
    this->damage->set_type(damage);
}
