//#include "battlefield.h"
#include <QApplication>
#include "field.h"
#include "unit.h"
#include "base.h"
/*
 * объяснить virtual = 0;
const  создание +
const iteraror +
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
        d2->move(9,8);
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
    Field field(10,10,100);
    auto base = new Base(&field);
    field.addItem(3, 6, base);

    for(unsigned int i = 0; i < 10; i++){
            for(unsigned int j = 0; j < 10; j++){
                if((j*i) % 3 == 1){
                    Proxy* landsc = new Proxy("D");
                    field.addLand(i, j, landsc);
                }
                else if ((j*i) % 2 == 0) {
                    Proxy* landsc = new Proxy("R");
                    field.addLand(i, j, landsc);
                }
                else {
                    Proxy* landsc = new Proxy("F");
                    field.addLand(i, j, landsc);
                }
            }
        }

/*
    for(auto i =0; i<10; i++){
        for(auto j = 0; j<10; j++){
            switch ((i+j)%10) {
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
*/
//    for (FieldIterator i(&field); i.isActive();++i){
//        std::cout << i->about() << std::endl;
//    }


//    auto *b1= melee->createDire();
    auto b1 = base->addOrk(0,1);
    base->addWitch(5,8);
    base->addChimera(4,6);
    base->addDragon(2,6);
    base->addKnight(3,5);
    base->addKnight(3,7);
//    field.addItem(0,0,b1);
    std::cout << field.getShortInfo() << std::endl;
    b1->move(3,3);
    std::cout << field.getShortInfo() << std::endl;
//    Field field2 = field;
    base->deleteUnit(b1);
    std::cout << field.getShortInfo() << std::endl;
    std::cout << "Item counter for field near base: " << base->getItemCounter() << std::endl;
}


int main()
{
//    QApplication a(argc, argv);
//    BattleField w;
//    w.show();
//    return a.exec();
    test2();
}
