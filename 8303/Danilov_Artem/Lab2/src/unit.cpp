//
// Created by kot on 25.02.2020.
//

#include "unit.h"

Unit::Unit(Unit &unit):
    name(unit.name), movable(unit.movable),
    naturalStats(unit.naturalStats), moveMediator(nullptr){}

std::string Unit::about()
{
    std::string output;
    output += shortName() + "\n";
    output += this->name + "\nCharacteristics:";
    output += "\nHealth: " + std::to_string(naturalStats.getHealth()) +
              "\nDamage: " + std::to_string(naturalStats.getDamage()) +
              "\nArmor: " + std::to_string(naturalStats.getArmor()) +
              "\nStrength: " + std::to_string(naturalStats.getStrength()) +
              "\nAgility: " + std::to_string(naturalStats.getAgility()) +
              "\nIntelligent: " + std::to_string(naturalStats.getIntelligence());
    return output+"\n";
}

void Unit::setMoveMediator(MoveMediator *value)
{
    moveMediator = value;
}

Knight::Knight(){
    name = "Zinaid, protector of your King";
    naturalStats.setAll(50,20,15);
}

Ork::Ork(){
    name = "Sasha, big but not smart Ork";
    naturalStats.setAll(60,15,5);
}

Dryad::Dryad(){
    name = "Grafinya, Defender of the nature";
    naturalStats.setAll(20,40,45);
}

Witch::Witch(){
    name = "Alena, she's never alone";
    naturalStats.setAll(15,35,60);
}

Dragon::Dragon(){
    name = "Druzhok, The richest being in the world";
    naturalStats.setAll(120,10,90);
}

Chimera::Chimera(){
    name = "Myaus, So toxic and danger";
    naturalStats.setAll(100,80,50);
}

void Unit::move(int x, int y){
    moveMediator->notify(this, x, y);
}
