#include "field/field.h"

class Test {
public:
    static void test1() {
        Field mainField(5,5,3,3,4,4);
        mainField.addUnit(0,0,'S',1);
        mainField.addNeutral(1,1,'w');
        mainField.printField();
        mainField.moveUnit(0,0,0,1,1);
        mainField.printField();
        mainField.moveUnit(0,1,1,1,1);
        mainField.printField();
    }

    static void test2() {
        Field mainField(3,3,0,0,2,2);
        mainField.addUnit(0,0,'E',2);
        mainField.addUnit(1,0,'W',1);
        mainField.printField();
        mainField.moveUnit(0,0,1,0,2);
        mainField.printField();
    }

    static void test3() {
        Field mainField(5,5,0,0,4,4);
        mainField.addUnit(0,1,'S',1);
        mainField.addUnit(1,0,'E',2);
        mainField.addUnit(1,1,'W',1);
        mainField.printField();
        mainField.moveUnit(1,1,1,0,1);
        mainField.printField();
    }
};

int main() {
    Test::test3();

}