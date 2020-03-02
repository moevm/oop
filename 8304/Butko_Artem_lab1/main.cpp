#include <iostream>
#include "GameField.h"
#include "Units.h"

int main()
{
    GameField Field(10,10);
    Field.showField();
    Field.addUnit('N', 1, 1);
    Field.addUnit('S', 5, 5);
    Field.addUnit('M', 20, 20);
    Field.showField();
    Field.moveUnit(5, 5, 10, 10);
    std::cout << std::endl;
    Field.showField();
    GameField tmpField(10, 10);
    std::cout << std::endl;
    tmpField = Field;
    tmpField.showField();
    std::cout << std::endl;
    tmpField.showField()
}
