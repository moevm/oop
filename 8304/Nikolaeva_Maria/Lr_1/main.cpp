#include <iostream>
#include "GameField/gamefield.h"
#include "Unit/swordsman.h"
#include "Unit/liveshield.h"
#include <Windows.h>

void printField(GameField* field) {
    system("cls");
    std::string buffer;

    for (int i = 0; i < field->getHeight(); ++i) {
        for (int j = 0; j < field->getWidth(); ++j) {
            if (field->getCell(j, i)->isEmpty()) {
                buffer += ". ";
            }
            else {
                buffer += "U ";
            }
        }
        buffer += "\n";
    }

    std::cout << buffer;
}


void test1() {
    std::cout << "Test 1" << std::endl;
    Sleep(2000);

    GameField* field = new GameField(10, 10);
    Mediator* mediator = new Mediator(field);

    Unit* unit1 = new Swordsman(mediator);
    Unit* unit2 = new LiveShield(mediator);

    unit1->setCoordinate(new Point2D(0, 0));
    unit2->setCoordinate(new Point2D(2, 3));

    field->addUnit(unit1);
    field->addUnit(unit2);
    printField(field);

    Sleep(2000);
    field->deleteUnit(unit2);
    printField(field);

    Sleep(2000);
    system("cls");
}


void test2() {
    std::cout << "Test 2" << std::endl;
    Sleep(2000);

    GameField* field = new GameField(10, 10);
    Mediator* mediator = new Mediator(field);

    Unit* unit1 = new Swordsman(mediator);
    Unit* unit2 = new LiveShield(mediator);

    unit1->setCoordinate(new Point2D(0, 0));
    unit2->setCoordinate(new Point2D(2, 3));

    field->addUnit(unit1);

    printField(field);

    GameField* newField = field->clone();
    field->addUnit(unit2);

    printField(field);
    std::cout << "OLD FIELD\n";
    Sleep(2000);
    printField(newField);
    std::cout << "NEW FIELD\n";

    Sleep(2000);
    system("cls");
}


void test3() {
    std::cout << "Test 3" << std::endl;
    Sleep(2000);

    GameField* field = new GameField(10, 10);
    Mediator* mediator = new Mediator(field);

    Unit* unit1 = new Swordsman(mediator);
    unit1->setCoordinate(new Point2D(0, 0));

    field->addUnit(unit1);

    while (unit1->move(1, 1)) {
        Sleep(150);
        printField(field);
    }

    std::cout << field->getNumberOfUnits() << std::endl;
    field->deleteUnit(unit1);
    std::cout << field->getNumberOfUnits() << std::endl;
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
