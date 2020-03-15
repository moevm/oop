#include <iostream>
#include "Unit.h"

Unit::Unit() {

}

void Unit::death(){
    std::cout << "The unit " << this->name << " was killed" << std::endl;
    this->notify();
}

void Unit::wasAttack(int damage){
    std::cout << "The unit " << this->name << " was attacked" << std::endl;
    std::cout << "The health before: " << this->condition.health << std::endl;
    this->condition.health -= damage;
    std::cout << "The health after: " << this->condition.health << std::endl;

    if (this->condition.health <= 0){
        this->death();
    }
}





