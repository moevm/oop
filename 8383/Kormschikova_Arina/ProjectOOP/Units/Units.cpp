#include <iostream>

#include "Units.h"
#include "Map.h"
#include "GameBlock.h"
#include "NeutralObject.h"



void Unit::showStat(){
    std::cout<<type<<std::endl<<"HP:"<<hitPoint<<std::endl<<"MP:"<<manaPoint<<std::endl<<"Magic resist:"<<magicResistance<<std::endl<<"Armor:"<<armor<<std::endl;
}

void Unit::move(int x, int y, GameMap& map){
    if((map.getHeight() > (this->y+y)) && (map.getWidth() > (this->x+x)) && ((this->y+y) >= 0) && ((this->x+x) >= 0) ){
        GameBlock* nextBlock =map.getBlock(this->y+y, this->x+x);
        if(nextBlock->landscape->availability == false || nextBlock->unitOnBlock !=nullptr){
            std::cout<<"The passage is blocked"<<std::endl;
        }
        else{
            if(nextBlock->objectOnBlock != nullptr){
                *(nextBlock->objectOnBlock) += *this;
            }
            nextBlock->setUnit(this);
            map.getBlock(this->y, this->x)->deleteUnit();
            this->x += x;
            this->y += y;
        
        }
    }
    else{
        std::cout<<"The passage is blocked"<<std::endl;
    }
}

void Unit::getDamage(int damage){
    this->hitPoint -= damage;
    if (hitPoint<1){
        this->death();
        std::cout<<"Unit "<<this->type<<" get damage "<<damage<<" and die"<<std::endl;
    }
    else{
        std::cout<<"Unit "<<this->type<<" get damage. "<<damage<<" HP:"<<this->hitPoint<<std::endl;
    }
}

void Unit::death(){
    delete this;
}


void Unit::update(){
    
}


bool Unit::checkForAttack(int x, int y){
    if ((x - this->x)*(x - this->x) + (y- this->y)*(y- this->y) <= (this->weapon->radius*this->weapon->radius)){
        return true;
    }
    return false;
}

void Unit::attack(Unit *enemy){
    int distanse = (enemy->x - this->x)*(enemy->x - this->x) + (enemy->y- this->y)*(enemy->y- this->y);
    enemy->getDamage(this->weapon->useWeapon(distanse, enemy->magicResistance, enemy->armor));
}
//----------------------------------------//

Rogue::Rogue(){
    this->hitPoint = 100;
    this->manaPoint = 20;
}

void Rogue::update(){
    std::cout<<"RUp"<<std::endl;
}

Ranger::Ranger(){
    this->magicResistance = 35;
    this->armor = 25;
    this->weapon = new Bow;
    this->type = 'R';
}


Slayer::Slayer(){
    this->magicResistance = 25;
    this->armor = 35;
    this->weapon = new Dagger;
    this->type = 'S';
}

//----------------------------------------------//
Mage::Mage(){
    this->hitPoint = 100;
    this->manaPoint = 100;
}

void Mage::update(){
    std::cout<<"MUp"<<std::endl;
}


BattleMage::BattleMage(){
    this->magicResistance = 40;
    this->armor = 35;
    this->weapon = new Hands;
    this->type = 'B';
}


Witch::Witch(){
    this->magicResistance = 60;
    this->armor = 10;
    this->weapon = new Staff;
    this->type = 'W';
}

//----------------------------//

Warrior:: Warrior(){
   this->hitPoint = 100;
   this->manaPoint = 10;
}


void Warrior::update(){
    std::cout<<"WUp"<<std::endl;
}


Paladin::Paladin(){
    this->magicResistance = 25;
    this->armor = 65;
    this->weapon = new Sword;
    this->type = 'P';
}


LanceKnight::LanceKnight(){
    this->magicResistance = 35;
    this->armor = 45;
    this->weapon = new Lance;
    this->type = 'L';
}
