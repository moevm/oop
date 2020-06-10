#ifndef INVOKER_H
#define INVOKER_H
#include <stack>
#include "Commands.h"

class Invoker
{
    std::stack <Command*> commands;
    GameField *field;
public:
    void setField(GameField*);
    void addBase(Base*, Coordinates, QPushButton*);
    void attackUnit(Coordinates, Coordinates);
    void createUnitToBase(Unit*, Coordinates);
    void deathUnit(Coordinates, unsigned);
    void destroyBase(Coordinates, unsigned, std::vector<Object**>);
    void entryFromBase(Object*&, Coordinates);
    void moveUnit(Coordinates, Coordinates);
    void undo();
};

#endif // INVOKER_H
