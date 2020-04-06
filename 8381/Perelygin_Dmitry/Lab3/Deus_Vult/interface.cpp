#include "interface.h"

void Interface::Game(){
    while(1)
    {
        std::cout << "Greetings!" << std::endl;
        std::cout << "1.Base control" << std::endl;
        std::cout << "2.Unit control" << std::endl;
        std::cout << "3.See map" << std::endl;
        std::cout << "4.Exit" << std::endl;
        //field->show_landscape();
        int choice1 = 0, choice2 = 0;
        std::cin >> choice1;
        switch(choice1){
        case 1:
            std::cout << "Command Base control" << std::endl;
            std::cout << "1.Placement Base" << std::endl;
            std::cout << "2.Create Unit" << std::endl;
            std::cout << "3.Back" << std::endl;
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
                        field->show_base();
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
                        break;
                    case 2:
                        unit_id = base->createCrusaderUnit(Horseman_ID,1, field, base);
                        break;
                    case 3:
                        unit_id = base->createCrusaderUnit(Archer_ID,1, field, base);
                        break;
                    case 4:
                        unit_id = base->createArabUnit(Infantryman_ID,1, field, base);
                        break;
                    case 5:
                        unit_id = base->createArabUnit(Horseman_ID,1, field, base);
                        break;
                    case 6:
                        unit_id = base->createArabUnit(Archer_ID,1, field, base);
                        break;

                       }
                    std::cout << "Enter x and y" << std::endl;
                    //std::cout << "If you want to back Enter -1 -1 " << std::endl;
                    std::cin >> x >> y;
                    if (x>-1 && y>-1)
                    {
                        Unit* un = base->get_Unit(unit_id);
                        field->add_unit(un,x,y);
                        field->show_id();
                    }
                break;
            }

            break;
        case 2:
            std::cout << "Command Unit control" << std::endl;
            std::cout << "1.Move" << std::endl;
            std::cout << "2.Attack" << std::endl;
            std::cout << "3.Back" << std::endl;
            std::cin >> choice2;
            switch(choice2)
            {
                case 1:
                std::cout << "Command Move" << std::endl;
                std::cout << "Enter Unit id, x, y" << std::endl;
                std::cin >>  unit_id >> x >> y;
                base->get_Unit(unit_id)->move_unit(x,y);
                field->show_id();
                break;

                case 2:
                std::cout << "Command attack" << std::endl;
                std::cout << "Enter Attacker Unit id, Defender Unit id" << std::endl;
                std::cin >>  unit_id >> def_unit_id;
            {Unit* def = base->get_Unit(def_unit_id);
                base->get_Unit(unit_id)->attack_unit(&def);
                std::cout << base->get_Unit(def_unit_id)->get_hp() << std::endl;
                field->show_id();
            }
                break;
                case 3:
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
        case 4:
            return;
            break;

        default:
            continue;
            break;
        }

    }


}
