#include <QCoreApplication>
#include <iostream>
#include <unitsinterface.h>
#include <field.h>
#include <unitsclasses.h>
#include <abstractFactory.h>

void example1();
void example2();
void example3();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Field field(3, 3, 3); //создание
    Field anotherField(field); //копирование
    Field oneanotherfield(std::move(field)); //перемещение
    example1();
    //example2();
    //example3();
}

void example1()
{
    Field* field = new Field(5, 5, 5);

    /*IteratorForField it(field);
    it.begin();
    it.getNext();
    it.getNext();*/

    std::cout << "Example 1\n";
    std::cout << "Field size: " << field->getNmRows() << " rows, " << field->getNmColumns() << " columns.\n";

    std::cout << "Adding a CritArcher to position [1][2] and an DamageAbsorberCavalry to [2][4] \n\n";

    CritUnitsFactory* crit1 = new CritUnitsFactory;
    DamageAbsorberUnitsFactory* abs1 = new DamageAbsorberUnitsFactory;

    field->addObject(1, 2, crit1->createArcher());
    field->addObject(2, 4, abs1->createCavalry());

    std::cout << field->getStringInfo().toStdString() << "\n\n";
}

void example2()
{
    Field* field = new Field(6, 7, 4);

    std::cout << "Example 2\n";
    std::cout << "Field size: " << field->getNmRows() << " rows, " << field->getNmColumns() << " columns.\n";

    std::cout << "Adding a CritInfantry to position [0][3] \n\n";

    CritUnitsFactory* crit1 = new CritUnitsFactory;
    field->addObject(0, 3, crit1->createInfantry());

    std::cout << field->getStringInfo().toStdString() << "\n";
    std::cout << "Now move it to the [0][1] \n\n";

    field->moveObject(0, 3, 0, 1);
    std::cout << field->getStringInfo().toStdString() << "\n\n";
}

void example3()
{
    Field* field = new Field(5, 3, 6);

    std::cout << "Example 3\n";
    std::cout << "Field size: " << field->getNmRows() << " rows, " << field->getNmColumns() << " columns.\n";

    std::cout << "Adding a DamageAbsorberInfantry to position [2][0] \n\n";

    DamageAbsorberUnitsFactory* absorbersFactory = new DamageAbsorberUnitsFactory;
    field->addObject(2, 0, absorbersFactory->createInfantry());

    std::cout << field->getStringInfo().toStdString() << "\n";
    std::cout << "Now delete it from the field \n\n";

    field->removeObject(2, 0);
    std::cout << field->getStringInfo().toStdString() << "\n\n";
}
