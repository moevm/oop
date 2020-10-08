//#include <QApplication>
#include "Field/field.h"
#include "Units/unit.h"
#include "Base/base.h"
#include "NeutralObject/armor.h"
#include "NeutralObject/context.h"
#include "NeutralObject/curse.h"
#include "NeutralObject/elixir.h"
#include "NeutralObject/weapon.h"
// TODO расскрашивать юнитов с зеленый и красный
// TODO component from {} to \t

//void test1(){
//
//    std::cout << "Hello, this is my first game\n";
//    Field field(10,10,4);
//    try {
//	    field.addUnit(d1, 0, 0, 0);
//	    field.addUnit(d2, 0, 1, 0);
//	    field.addUnit(r1, 9, 9, 0);
//	    field.addUnit(r2, 9, 8, 0);
//
//    } catch (std::logic_error err) {
//        std::cout << "Error: " << err.what() << std::endl;
//    }
//    std::cout <<"try to move unit from (0,1) to (9,9)" <<std::endl;
//    try {
//        d2->move(9,8);
//    } catch (std::logic_error err) {
//        std::cout << "Error: " << err.what() << std::endl;
//    }
//    std::cout << field.getAbout(9,9) << std::endl;
//
//    std::cout <<"try to move away from field" <<std::endl;
//    try {
//        d1->move(-1,-10);
//    } catch (std::logic_error err) {
//        std::cout << "Error: " << err.what() << std::endl;
//    }
//    std::cout <<"Try to add after limit of units has reached to (7,7)" <<std::endl;
//    try {
//	    field.addUnit(r2, 7, 7, 0);
//
//    } catch (std::logic_error err) {
//        std::cout << "Error: " << err.what() << std::endl;
//    }
//    std::cout << field.getAbout(7,7) << std::endl;
//    std::cout << field.getAbout(0,0) << std::endl;
//    std::cout << field.getAbout(0,1) << std::endl;
//    std::cout << field.getAbout(1,0) << std::endl;
//    std::cout << field.getAbout(9,9) << std::endl;
//    std::cout << field.getAbout(9,8) << std::endl;
//
//    std::cout <<"copy field" <<std::endl;
//    Field field2 = field;
//
//    std::cout << field2.getAbout(0,0) << std::endl;
//    std::cout << field2.getAbout(0,1) << std::endl;
//    std::cout << field2.getAbout(1,0) << std::endl;
//    std::cout << field2.getAbout(9,9) << std::endl;
//    std::cout << field2.getAbout(9,8) << std::endl;
//
//    std::cout << field.getAbout(10,100) << std::endl;
//
//}

//void test2(){
//    Field field(10,10,100);
//    auto base = new Base(&field);
//	field.addUnit(base, 3, 6, 0);
//
//    for(unsigned int i = 0; i < 10; i++){
//            for(unsigned int j = 0; j < 10; j++){
//	            if((j*i) % 3 == 1){
//		            Proxy* landsc = new Proxy("D");
//		            field.addLand(i, j, landsc);
//	            }
//	            else if ((j*i) % 2 == 0) {
//		            Proxy* landsc = new Proxy("R");
//		            field.addLand(i, j, landsc);
//	            }
//	            else {
//		            Proxy* landsc = new Proxy("F");
//		            field.addLand(i, j, landsc);
//	            }
//            }
//        }
//    std::cout << field.getShortInfo() << std::endl;

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
                field.addUnit(i,j,range->createRadiant());
                break;

            }
        }
    }
*/
//    for (FieldIterator i(&field); i.isActive();++i){
//        std::cout << i->about() << std::endl;
//    }


////    auto *b1= melee->createDire();
//    auto b1 = base->addOrk(0,1);
//    base->addWitch(5,8);
//    base->addChimera(4,6);
//    base->addDragon(2,6);
//    base->addKnight(3,5);
//    base->addKnight(3,7);
////    base->field->deleteUnit(3,6);
////    field.addUnit(0,0,b1);
//    std::cout << field.getShortInfo() << std::endl;
//    b1->move(3,3);
//    std::cout << field.getShortInfo() << std::endl;
////    Field field2 = field;
//    base->deleteUnit(b1);
//    std::cout << field.getShortInfo() << std::endl;
//    std::cout << "Item counter for field near base: " << base->getItemCounter() << std::endl;
//}


void test2(){
	std::cout << "Hello, this is my first game\n";
    Field field(10,10,4);
    Base * base = new Base(10, 100, 4, 4, 1);
	field.setBase(base);
	field.addUnit(base->createUnit("Ork"), 3, 2, 1);
	field.addUnit(base->createUnit("Ork"), 0, 0, 1);
	field.addUnit(base->createUnit("Dragon"), 0, 1, 1);
	field.addUnit(base->createUnit("Chimera"), 3, 3, 1);
	field.deleteUnit(3,3);
	field.addNeutral(new GetElixir(new TheAncientDrink()), 1, 0);
	cout<<field.getUnitMap()<<endl;
	cout<<field.getLandMap()<<endl;
	cout<<field.getNeutralMap()<<endl;
	cout<<field.getBase()->printUnits()<<endl;
	cout<<field.getAbout(0,0)<<endl;
	field.moveUnit(field.getItem(0,0)->getUnit(),1 ,0);
	cout<<field.getUnitMap()<<endl;
	cout<<field.getLandMap()<<endl;
	cout<<field.getNeutralMap()<<endl;
	cout<<field.getBase()->printUnits()<<endl;
	cout<<field.getAbout(1,0)<<endl;

}

int main()
{
    test2();
}
