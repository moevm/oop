#include "interface.h"
#include "loging.h"
#include "saver.h"
#include "well.h"
#include "forge.h"
#include "armory.h"
#include "stable.h"

void Interface::Game(){

    std::cout << "Greetings! What kind of log you want?" << std::endl;
    std::cout << "1.Terminal" << std::endl;
    std::cout << "2.File" << std::endl;
    int log = 0 ;
    std::cin >> log;   
    loging* Logs = new loging();

    NeturalObjects* well = new Well();
    NeturalObjects* forge = new Forge();
    NeturalObjects* armory = new Armory();
    NeturalObjects* stable = new Stable();
    Saver* save = new Saver(field,Logs,well, forge,armory,stable);
    Logs->initialization(log);
    save->add_crus_base(base);
    while(1)
    {


        std::cout << "Greetings!" << std::endl;
        std::cout << "1.Base control" << std::endl;
        std::cout << "2.Unit control" << std::endl;
        std::cout << "3.Make Save" << std::endl;
        std::cout << "4.Load Save" << std::endl;
        //std::cout << "3.See map" << std::endl;
        std::cout << "5.Exit" << std::endl;
        //field->show_landscape();
        int choice1 = 0, choice2 = 0, choice3 = 0;
        std::cin >> choice1;
        switch(choice1){
        case 1:
            std::cout << "Command Base control" << std::endl;
            std::cout << "1.Placement Base" << std::endl;
            std::cout << "2.Create Unit" << std::endl;
            std::cout << "3.Create net obj" << std::endl;
            std::cout << "4.Back" << std::endl;
            std::cin >> choice2;
            switch(choice2)
            {
                case 1:
                    std::cout << "Command Placement Base" << std::endl;
                    std::cout << "Enter x and y" << std::endl;
                    //std::cout << "If you want to back Enter -1 -1 " << std::endl;
                    std::cin >> x >> y;
                    if (x>-1 && y>-1)
                    {
                        field->add_base(base,x,y);
                        base->set_pos(x,y);
                        //field->show_base();
                        Logs->No_varible(1);
                    }
                break;
                case 2:
                    std::cout << "Command Create Unit" << std::endl;
                    std::cout << "------------UNIT TYPES--------------" << std::endl;
                    std::cout << "1.Crusader" << std::endl;
                    std::cout << "2.Knight" << std::endl;
                    std::cout << "3.Crusaderarcher" << std::endl;
                    std::cout << "4.Arab" << std::endl;
                    std::cout << "5.Camelrider" << std::endl;
                    std::cout << "6.Arabarcher" << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                    std::cout << "Enter type" << std::endl;
                    //std::string type_name;
                    std::cin >> type;
                    switch (type) {
                    case 1:
                        unit_id = base->createCrusaderUnit(Infantryman_ID,1, field, base);
                        Logs->No_varible(3);
                        break;
                    case 2:
                        unit_id = base->createCrusaderUnit(Horseman_ID,1, field, base);
                        Logs->No_varible(3);
                        break;
                    case 3:
                        unit_id = base->createCrusaderUnit(Archer_ID,1, field, base);
                        Logs->No_varible(3);
                        break;
                    case 4:
                        unit_id = base->createArabUnit(Infantryman_ID,1, field, base);
                        Logs->No_varible(2);
                        break;
                    case 5:
                        unit_id = base->createArabUnit(Horseman_ID,1, field, base);
                        Logs->No_varible(2);
                        break;
                    case 6:
                        unit_id = base->createArabUnit(Archer_ID,1, field, base);
                        Logs->No_varible(2);
                        break;

                       }
                    std::cout << "Enter x and y" << std::endl;
                    //std::cout << "If you want to back Enter -1 -1 " << std::endl;
                    std::cin >> x >> y;
                    if (x>-1 && y>-1)
                    {
                        Unit* un = base->get_Unit(unit_id);
                        field->add_unit(un,x,y);
                        //field->show_id();
                    }
                break;

            case 3:
            std::cout << "Netural objects control" << std::endl;
            std::cout << "1.Placement well" << std::endl;
            std::cout << "2.Placement forge" << std::endl;
            std::cout << "3.Placement armory" << std::endl;
            std::cout << "4.Placement stable" << std::endl;
            std::cout << "5.Back" << std::endl;
            std::cin >> choice3;
            switch (choice3) {
            case 1:
                std::cout << "set x, y" << std::endl;
                std::cin >> x >> y;
                field->add_netural_obj(well,x,y,1);
                Logs->No_varible(4);
            break;

            case 2:
                std::cout << "set x, y" << std::endl;
                std::cin >> x >> y;
                field->add_netural_obj(forge,x,y,2);
                Logs->No_varible(7);
            break;

            case 3:
                std::cout << "set x, y" << std::endl;
                std::cin >> x >> y;
                field->add_netural_obj(armory,x,y,3);
                Logs->No_varible(5);
            break;

            case 4:
                std::cout << "set x, y" << std::endl;
                std::cin >> x >> y;
                field->add_netural_obj(stable,x,y,4);
                Logs->No_varible(6);
            break;

            case 5:
            continue;
            break;

            }
            continue;
            break;
        }

            break;
        case 2:
            std::cout << "Command Unit control" << std::endl;
            std::cout << "1.Move" << std::endl;
            std::cout << "2.Attack" << std::endl;
            std::cout << "3.Touch object" << std::endl;
            std::cout << "4.Back" << std::endl;
            std::cin >> choice2;
            switch(choice2)
            {
                case 1:
                std::cout << "Command Move" << std::endl;
                std::cout << "Enter Unit id, x, y" << std::endl;
                std::cin >>  unit_id >> x >> y;
                base->get_Unit(unit_id)->move_unit(x,y,Logs);
                //field->show_id();
                continue;
                break;

                case 2:
                std::cout << "Command attack" << std::endl;
                std::cout << "Enter Attacker Unit id, Defender Unit id" << std::endl;
                std::cin >>  unit_id >> def_unit_id;
            {Unit* def = base->get_Unit(def_unit_id);
                base->get_Unit(unit_id)->attack_unit(&def,Logs);
                //std::cout << base->get_Unit(def_unit_id)->get_hp() << std::endl;
                //field->show_id();
                break;

            }
                continue;
                break;

                case 3:
                std::cout << "Command touch object" << std::endl;
                std::cout << "Enter Unit id, x, y" << std::endl;
                std::cin >> unit_id >> x >> y;
                *(field->get_obj(x,y))+=*(base->get_Unit(unit_id));
                if (field->get_obj_type(x,y)==1)
                    Logs->No_varible(9);
                if (field->get_obj_type(x,y)==2)
                    Logs->No_varible(10);
                if (field->get_obj_type(x,y)==3)
                    Logs->No_varible(11);
                if (field->get_obj_type(x,y)==4)
                    Logs->No_varible(12);
                break;

                case 4:
                continue;
                break;

            }
       /* case 3:
            std::cout << "Command See map" << std::endl;
            std::cout << "1.Unit map" << std::endl;
            std::cout << "2.Landscape map" << std::endl;
            std::cout << "3.Base map" << std::endl;
            std::cout << "4.Netural obj map" << std::endl;
            std::cout << "5.Back" << std::endl;
            std::cin >> choice2;
            break;*/

        case 3:

        save->make_save();
        break;

        case 4:
        field->clear_obj();
        field->clear_unit();
        base->clear_base();
        save->make_load();
        break;

        case 5:
            return;
            break;

        default:
            continue;
            break;
        }

    }


}
