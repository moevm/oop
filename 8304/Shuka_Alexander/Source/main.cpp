#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "UnitBuilder/unitdirector.h"
#include "Field/gamefield.h"

/*
 * This code was created to demonstrate the functionality
 * of the program. It is not part of the project.
 *
 * Be understanding.
 */


enum class MOVE : int
{
    LEFT = 0,
    DOWN = 1,
    UP = 2,
    RIGHT = 3,
    STOP = 4
};


void printField(const GameField& field) {
    // system("cls");
    for (size_t a = 0; a < field.getHeight(); ++a) {
        for (size_t  b = 0; b < field.getWidth(); ++b) {
            if (field.isEmpty(Point2D(b, a))) {
                std::cout << ". ";
            }
            else {
                std::cout << "1 ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void itField(const GameField& field) {
    auto it = field.getIterator();
    for (it->first(); it->hasNext(); ++*it) {
        **it;
        std::cout << "a";
    }
}


MOVE input() {
    if (kbhit()) {
        switch (getch()) {
        case 'w':
            return MOVE::UP;
        case 's':
            return MOVE::DOWN;
        case 'a':
            return MOVE::LEFT;
        case 'd':
            return MOVE::RIGHT;
        }
    }
    return MOVE::STOP;
}


bool logic(std::shared_ptr<Unit> unit, GameField& field) {
    MOVE a = input();
    Point2D point = unit->getPosition();

    switch (a) {
    case MOVE::UP:
        if (point.y > 0) {
            point.y--;
            if (field.isEmpty(point)) {
                field.moveUnit(unit, point);
                unit->moveTop();
                return true;
            }
        }
        break;
    case MOVE::DOWN:
        if (point.y + 1 < field.getHeight()) {
            point.y++;
            if (field.isEmpty(point)) {
                field.moveUnit(unit, point);
                unit->moveBottom();
                return true;
            }
        }
        break;
    case MOVE::LEFT:
        if (point.x > 0) {
            point.x--;
            if (field.isEmpty(point)) {
                field.moveUnit(unit, point);
                unit->moveLeft();
                return true;
            }
        }
        break;
    case MOVE::RIGHT:
        if (point.x + 1 < field.getWidth()) {
            point.x++;
            if (field.isEmpty(point)) {
                field.moveUnit(unit, point);
                unit->moveRight();
                return true;
            }
        }
    };
    return false;
}


void game() {
    GameField field(15, 15);
    UnitDirector director;
    auto unit = director.createDragon(Point2D(0, 0));

    field.addUnit(unit);

    while (true) {

        if (logic(unit, field)) {
            printField(field);
        }
    }
}


void test() {
    GameField field(15, 15);
    UnitDirector director;
    Point2D point(0, 0);

    auto unit = director.createDragon(point);
    field.addUnit(unit);
    point.x++;

    unit = director.createThief(point);
    point.x++;
    field.addUnit(unit);

    unit = director.createTower(point);
    point.x++;
    field.addUnit(unit);

    unit = director.createWarrior(point);
    point.y++;
    field.addUnit(unit);

    Point2D point1(7, 7);
    auto unit1 = director.createWarrior(point1);
    field.addUnit(unit1);

    unit = director.createGoldMiner(point);
    point.y++;
    field.addUnit(unit);

    unit = director.createKamikadze(point);
    field.addUnit(unit);

    printField(field);

    field.deleteUnit(unit);

    printField(field);
}


int main() {    
    game();
    //test();
    return 0;
}
