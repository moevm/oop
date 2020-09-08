#include "Damage.h"
void Damage::set_type(std::string type_damage){
    if (type_damage == "light"){
        this->type_damage = "light";
        this->multiply = 5;
    }
    if (type_damage == "pierce"){
        this->type_damage = "pierce";
        this->multiply = 15;
    }
    if (type_damage == "hard"){
        this->type_damage = "hard";
        this->multiply = 20;
    }
    if (type_damage == "null"){
        this->type_damage = "null";
        this->multiply = 0;
    }

}