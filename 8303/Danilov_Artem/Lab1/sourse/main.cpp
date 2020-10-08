//#include "battlefield.h"
#include <QApplication>
#include "field.h"
#include "Units/unit.h"
/*
max count +
copy+
столкновение+
создание в занятое место+
вне пол+


удаление существующего
удаление несуществующего
удаление вне поля+
after iter +
get about +
get short names +
*/
void test1(){
    UnitFactory * melee = new MeleeFactory;
    UnitFactory * support = new SupportFactory;
    auto *d1 = melee->createDire();
    auto *r1 = melee->createRadiant();
    auto *d2 = support->createDire();
    auto *r2 = support->createRadiant();
    std::cout << "Hello, this is my first game\n";
    Field field(10,10,4);
    try {
        field.addItem(0,0,d1);
        field.addItem(0,1,d2);
        field.addItem(9,9,r1);
        field.addItem(9,8,r2);

    } catch (std::logic_error err) {
        std::cout << "Error: " << err.what() << std::endl;
    }
    std::cout <<"try to move unit from (0,1) to (9,9)" <<std::endl;
    try {
        d2->move(9,9);
    } catch (std::logic_error err) {
        std::cout << "Error: " << err.what() << std::endl;
    }
    std::cout << field.getAbout(9,9) << std::endl;

    std::cout <<"try to move away from field" <<std::endl;
    try {
        d1->move(-1,-10);
    } catch (std::logic_error err) {
        std::cout << "Error: " << err.what() << std::endl;
    }
    std::cout <<"Try to add after limit of units has reached to (7,7)" <<std::endl;
    try {
        field.addItem(7,7,r2);

    } catch (std::logic_error err) {
        std::cout << "Error: " << err.what() << std::endl;
    }
    std::cout << field.getAbout(7,7) << std::endl;
    std::cout << field.getAbout(0,0) << std::endl;
    std::cout << field.getAbout(0,1) << std::endl;
    std::cout << field.getAbout(1,0) << std::endl;
    std::cout << field.getAbout(9,9) << std::endl;
    std::cout << field.getAbout(9,8) << std::endl;

    std::cout <<"copy field" <<std::endl;
    Field field2 = field;

    std::cout << field2.getAbout(0,0) << std::endl;
    std::cout << field2.getAbout(0,1) << std::endl;
    std::cout << field2.getAbout(1,0) << std::endl;
    std::cout << field2.getAbout(9,9) << std::endl;
    std::cout << field2.getAbout(9,8) << std::endl;

    std::cout << field.getAbout(10,100) << std::endl;

}

void test2(){
    UnitFactory * melee = new MeleeFactory;
    UnitFactory * support = new SupportFactory;
    UnitFactory * range = new RangeFactory;
    Field field(10,10,100);

    for(auto i =0; i<10; i++){
        for(auto j = 0; j<10; j++){
            switch ((i+j)%12) {
            case 0:
                field.addItem(i,j,melee->createDire());
                break;
            case 1:
                field.addItem(i,j,melee->createRadiant());
                break;
            case 2:
                field.addItem(i,j,support->createDire());
                break;
            case 3:
                field.addItem(i,j,support->createRadiant());
                break;
            case 4:
                field.addItem(i,j,range->createDire());
                break;
            case 5:
                field.addItem(i,j,range->createRadiant());
                break;

            }
        }
    }

    for (FieldIterator i(&field); i.isActive();++i){
        std::cout << i->about() << std::endl;
    }
    std::cout << field.getShortInfo() << std::endl;
    std::cout << "Item counter for field1: " << field.getItemCounter() << std::endl;
    std::cout <<"Coppy field and delete median elements" <<std::endl;
    Field field2 = field;
    for (auto  i = 0; i<10; i++){
        field2.deleteItem(i,i);
    }

    std::cout << field2.getShortInfo() << std::endl;
    std::cout << "Item counter for field2: " << field2.getItemCounter() << std::endl;
}


int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    BattleField w;
//    w.show();
//    return a.exec();
    test1();
}
