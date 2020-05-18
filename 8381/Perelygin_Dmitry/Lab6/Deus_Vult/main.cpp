#include <iostream>
#include "unit.h"
#include "cavalry.h"
#include "shooter.h"
#include "crusader.h"
#include "arab.h"
#include "arabarcher.h"
#include "crusaderarcher.h"
#include "knight.h"
#include "camelrider.h"
#include "field.h"
#include "fabrics.h"
#include "arab_fabric.h"
#include "crusader_fabric.h"
#include "base.h"
#include "landscapes.h"
#include "forest.h"
#include "plain.h"
#include "mountain.h"
#include "neturalobjects.h"
#include "well.h"
#include "armory.h"
#include "forge.h"
#include "stable.h"
#include "interface.h"

using namespace std;

int main()
{

    Interface* interface = new Interface();
    interface->Game();
    return 0;
    /*Field Battlefield(10,5);//создание поля
    Base* Castle = new Base();

    // Crusader *Man = new Crusader("Crusader1",&Battlefield);//создание двух юнитов
    //Knight *Horseman = new Knight("Knight1",&Battlefield);
    Unit *Man = Castle->createCrusaderUnit(Infantryman_ID,"Crusader1", &Battlefield, Castle);
    Unit *Horse = Castle->createCrusaderUnit(Horseman_ID,"Horse1", &Battlefield, Castle);


    //cout << "Horse ATTACK  "<< Horse->get_attack() << endl;//проверка доступа к данным объектов класса и успешность создания
    cout << "Crusader HP  "<< Man->get_hp() << endl;//проверка доступа к данным объектов класса и успешность создания


    Battlefield.show_field();//Показ поля до добавления юнитов на него

    cout << "Max count of unit on field "<<Battlefield.get_max_count() << endl;


    Battlefield.add_unit(Horse, 0,0);//Добавление Рыцаря и показ поля после
    Battlefield.show_field();

    Battlefield.add_unit(Man, 0,0);
    Battlefield.show_field();
    Battlefield.add_unit(Man, 2,1);//Добавление крестоносца на занятую и не занятую позицию
    //Man->set_position();
    cout << "IM HERE MAMA " << Man->get_x() << endl;
    Battlefield.show_field();
    Field Battlefield1(Battlefield);
    cout << "second field  "<< endl;
    Battlefield1.show_field();

    //Man->move_unit(2,2);
    Horse->show_debuffs();
    Horse->move_unit(2,2);// попытка передвинуться
    Battlefield.show_field();
    Horse->show_debuffs();
    cout << "DEMONSTRATION ATTACKS: " << endl;
    Horse->attack_unit(&Man);
     Horse->attack_unit(&Man);
      Horse->attack_unit(&Man);
       Horse->attack_unit(&Man);
        Horse->attack_unit(&Man);
         Horse->attack_unit(&Man);
          Horse->attack_unit(&Man);
    if (!(Man==nullptr))
    {
    cout << "Crusader's HP after attack - "<<Man->get_hp() << endl;
    }
    cout << "Field after fight: " << endl;
    Battlefield.show_field();
    cout << "Landscape" << endl;
    Battlefield.show_landscape();

    std::cout << Castle->get_unit_now() <<std::endl;



    NeturalObjects* well = new Well();
    Battlefield.add_netural_obj(well, 5, 5);
    cout << "Neutral Object Placement " << endl;
    Battlefield.show_net_obj();
    *well+=*Horse;
    cout << "before heal:" << endl;
    cout << Horse->get_hp() << endl;
    cout << "try to heal with Well:" << endl;
    cout << Horse->get_hp() << endl;
    Battlefield.add_base(Castle, 7, 7);
    cout << "Base Object Placement " << endl;
    Battlefield.show_base();
    return 0;*/

}
