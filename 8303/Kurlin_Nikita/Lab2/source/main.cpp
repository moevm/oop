#include "mainwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    GameField field(7, 7, 10);
    Base* base = field.setBase(3, 4, 3, 100);
    Base* base2 = field.setBase(6, 5, 3, 100);
    for (int i = 0; i < 100; i++)                   //
        base->createUnit("Flatbow");
    base->printAll();

    std::cout << "--------------------\n";          // Демонстрация 1 - создание юнитов, их смерть, реакция базы


    for (int i = 0; i < 100; i++){
        base2->createUnit("Spearman");              //
        base2->createUnit("Hussar");
    }

    base2->printAll();

    field.printAll();                             // Демонстрация 2 - размещение юнитов и баз на поле с учётом ландшафта

    /*Iterator iter(&field);
    while (iter.hasNext()){
        cout << (*iter)->armyType << endl;
        iter++;
    }*/

    DrinkPoison* drinkPoison = new DrinkPoison(new ArcherPoison);
    //GetArmor* getArmor = new GetArmor(new ArcherArmor);
    //GetWeapon* getWeapon = new GetWeapon(new ArcherWeapon);
    //GetMedicine* getMedicine = new GetMedicine(new ArcherMedicine);

    Iterator iter(&field);
    while (iter.hasNext()){
        //drinkPoison->drinkPoison(*iter);
        //getArmor->getArmor(*iter);                // Демонстрация 3 - взаимодействие юнитов с нейтральными объектами (яд для лучника)
        //getWeapon->getWeapon(*iter);
        *drinkPoison == *iter;
        iter++;
    }
    field.printAll();
    base->printAll();

    return 0;
    //return a.exec();
}
