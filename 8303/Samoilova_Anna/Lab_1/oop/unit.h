#ifndef UNIT_H
#define UNIT_H

#include <iostream>

class Unit  // виртуалный класс юнитов
{
private:
    unsigned int step;
    unsigned int attack;
    unsigned int health;
    bool child = false;
public:
    Unit();
    Unit(const Unit& original){
        step = original.get_step();
        attack = original.get_attack();
        health = original.get_health();
        child = original.get_is_child();
        this->let = original.let;
    }
    char let;
    unsigned int get_step() const;
    unsigned int get_attack() const;
    unsigned int get_health() const;
    bool get_is_child() const;
};



class Unit_1 : public Unit //Стрелки
{
public:
    Unit_1(){
        let = 'S';
    }
};

class Unit_11 : public Unit_1 //Лук(+здоровье)
{
public:
    Unit_11(){

    }
};

class Unit_12 : public Unit_1//Арбалет(+скорость)
{
public:
    Unit_12(){

    }
};



class Unit_2 : public Unit //Крылатые
{
private:
    int height;

public:
    Unit_2(){
        let = 'F';
    }
};

class Unit_21 : public Unit_2 //воздушный шар(+здоровье)
{
public:
    Unit_21(){

    }
};

class Unit_22 : public Unit_2 //параплан (+скорость)
{
public:
    Unit_22(){

    }
};



class Unit_3 : public Unit //Конница
{
public:
    Unit_3(){
        let = 'H';
    }
};

class Unit_31 : public Unit_3 //тяжелые рыцари(+здоровье)
{
public:
    Unit_31(){

    }
};

class Unit_32 : public Unit_3 //легкая конница(+сорость)
{
public:
    Unit_32(){

    }
};

#endif // UNIT_H
