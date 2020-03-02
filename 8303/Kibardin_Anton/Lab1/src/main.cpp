#include <iostream>

#include "Field.h"
#include "Dwarf.h"
#include "Paladin.h"
#include "Elf.h"
#include "Bard.h"
#include "Flamen.h"
#include "Necromancer.h"

int main() {
    puts("first example");
    puts("created first field");
    Field gameField(5,8);
    gameField.print();

    printf("add dwarf on field\n");
    Dwarf zoltan;
    gameField.addObject(&zoltan, 2, 2);
    gameField.print();

    printf("move dwarf\n");
    zoltan.move(3,5);
    gameField.print();

    printf("delete dwarf\n");
    zoltan.deleteFromField();
    gameField.print();


    puts("\nsecond example");
    Elf legolas;
    puts("add elf on field");
    gameField.addObject(&legolas, 1, 1);
    gameField.print();

    puts("move first field to second");
    Field newField(std::move(gameField));

    puts("second field");
    newField.print();

    puts("first field");
    gameField.print();


    puts("\nthird example");
    puts("create third field");
    Field third(5,5);

    puts("copy third field to first");
    gameField = third;

    puts("third field");
    third.print();

    puts("first field");
    gameField.print();

    puts("add dwarf to third field");
    third.addObject(&zoltan, 1, 1);
    third.print();

    puts("first field");
    gameField.print();
    return 0;
}
