#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>

class Unit {
public:
    int x, y;
    int health;
    int armor;
    int attack;
    std::string type;
    std::string name;
    void move(int, int);
};

class MeleeWarrior
    :public Unit {
protected:
    int melee_r;
};

class MediumWarrior
    :public Unit {
protected:
    int medium_r;
};

class DistanceWarrior
    :public Unit {
protected:
    int distance_r;
};

class Scorpio
    :public MeleeWarrior { //класс воинов "скорпион", ближний бой
public:
    Scorpio();
};

class Mammoth
    :public MeleeWarrior { //класс воинов "мамонт", ближний бой
public:
    Mammoth();
};

class Frog
    :public MediumWarrior { //класс воинов "лягушка", бой на средней дистанции
public:
    Frog();
};

class Kangaroo
    :public MediumWarrior { //класс воинов "кенгуру", бой на средней дистанции
public:
    Kangaroo();
};

class Swallow
    :public DistanceWarrior { //класс воинов "ласточка", дальний бой
public:
    Swallow();
};

class Hawk
    :public DistanceWarrior { //класс воинов "ястреб", дальний бой
public:
    Hawk();
};


#endif // UNIT_H
