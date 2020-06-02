#include "unit.h"
#include "landscape.h"
#include "nitralobject.h"
#include "base.h"
#ifndef FIELD_H
#define FIELD_H
#define COUNT_OF_UNITS_TYPE 6


/* отдел поля */

struct Cell{
    Unit* unit = nullptr;
    Base* base = nullptr;
    NitralObject* nObject = nullptr;
    Landscape* landScape = nullptr;
};

class Field{
private:
    int countOfDiffUnits = COUNT_OF_UNITS_TYPE;
    int rows;
    int columns;
    int countOfObjects;
    int maxNumOfObjects;
    Cell*** field;
    Unit*** units;                              // либо пофиксить эту матрицу и сделать её нормальным стеком, либо мараться с каждой функцией, ищущей юнита
public:
    Field(int M, int N, int maxNumOfObjects);
    Field(const Field& field);
    Field& operator= (const Field& field);
    Field(Field&& field);
    Field& operator=(Field&& field);
    int checkEmptySpace(int code);
    void setUnit1(Unit* unit);
    void deleteUnit1(Unit* unit);
    Unit* changeUnit1 (Unit* unit);
    void setUnit2(Unit* unit);
    void deleteUnit2(Unit* unit);
    Unit* changeUnit2(Unit* unit);
    void move(Unit* unit, int x, int y);
    void createBase(int x, int y);
    void setUnitFromBase(ArmyFactory& factory, int x, int y, int code);
    Unit* getLastUnit(int code);
    int getBaseGold(int x, int y);
    int getBaseCountOfUnits(int x, int y);
    void printField(Unit* unit);
    ~Field();
};

/* Паттерн команда */

class Command{
public:
    virtual void execute(Unit* unit) = 0;
protected:
    Command(Field* gameField) : gField(gameField){}
    Field* gField;
};

class MoveUpCommand: public Command{
public:
    MoveUpCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit);
};

class MoveDownCommand: public Command{
public:
    MoveDownCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit);
};

class MoveLeftCommand: public Command{
public:
    MoveLeftCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit);
};

class MoveRightCommand: public Command{
public:
    MoveRightCommand(Field* gameField) : Command(gameField){}
    void execute(Unit* unit);
};

#endif // FIELD_H
