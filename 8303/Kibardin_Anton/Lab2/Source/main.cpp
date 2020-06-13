#include <iostream>

#include "Field.h"
#include "Units/Bard.h"
#include "Units/Paladin.h"
#include "Units/Elf.h"
#include "Units/Bard.h"
#include "Units/Flamen.h"
#include "Units/Necromancer.h"
#include "Fabric.h"

int main() {
    Field gameField(5, 5);

    puts("first example");
    puts("gameField field");
    gameField.print();
    gameField.printLandscape();
    gameField.printNeutrals();
    puts("\nsecond example");
    puts("create base");

    Base* baseOne = gameField.setBase(1,1,5);
    gameField.print();
    puts("create units on base");
    baseOne->createUnit('d');
    baseOne->createUnit('e');
    baseOne->createUnit('p');

    gameField.print();

    puts("\nthird example\n");
    puts("get effect of snake poison");
    for(FieldIterator iter(&gameField); iter != nullptr; iter++)
    {
        Poison snakePoison;
        if((*iter)->getCharacter())
            snakePoison += (*iter)->getCharacter();
    }

    gameField.print();
    return 0;
}
