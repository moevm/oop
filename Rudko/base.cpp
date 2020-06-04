#include "base.h"
#include <string.h>

Base::Base(int x, int y, GField* field){
    this->field = field;
    if(field->map1[x][y]->type == "landscape" && !flag_base){
        Unit* BASE = new Unit;
        BASE->x = x;
        BASE->y = y;
        base_x = x;
        base_y = y;
        BASE->health = 1000;
        BASE->type = "base";
        BASE->name = "BASE";
        field->map1[x][y] = BASE;
        flag_base = 1;
    }
}

void Base::CreatureUnit(int x, int y, std::string Name){
    Unit* unit;
    //std::vector<std::vector<Unit*>> map = field->getMap();
    if(Name == "scorpio") { unit = new Scorpio();  }//num++; }
    if(Name == "mammoth") { unit = new Mammoth();  }//num++; }
    if(Name == "frog")    { unit = new Frog();     }//num++; }
    if(Name == "kangaroo"){ unit = new Kangaroo(); }//num++; }
    if(Name == "swallow") { unit = new Swallow();  }//num++; }
    if(Name == "hawk")    { unit = new Hawk();     }//num++; }
    if(field->map1[x][y]->type == "landscape"){
        counter++;
        if(counter > 7)
            std::cout << "На поле максимальное количество юнитов" << std::endl;
        else
            field->addUnit(unit, x, y);
    }
}

void Base::Condition(){
    std::cout << "Coordinats = " << base_x << ' ' << base_y << std::endl;
    std::cout << "Helth = " << base_helth << std::endl;
    std::cout << "People on the field = " << counter << std::endl;
}

void Base::Control(int x, int y, std::string answer){
    //std::cout << x << ' ' << y << std::endl;
    if(x >= field->getLength() || y >= field->getLength() || x < 0 || y < 0){
        std::cout << "Ввседите координаты удовлетворяющие полю" << std::endl;
    }
    else {
        if(answer != "L" && answer != "R" && answer != "U" && answer != "D")
            std::cout << "Введите существующие команды" << std::endl;
        else {
            if(answer == "L"){
                if(field->map1[x][y-1]->type == "landscape"){
                    if(field->getLand()->isMoved(field->map1[x][y]))
                        if(field->getLand()->isDamage(field->map1[x][y])){
                            field->map1[x][y]->health -= 3;
                            std::cout << "! Воин получил урон в размере 3 едениц !" << std::endl;
                            field->moveUnite(field->map1[x][y], x, y-1);
                            return;
                        }else {
                            field->moveUnite(field->map1[x][y], x, y-1);
                            return;
                        }
                    else{
                        std::cout << "Воин не может передвигаться по даннаму типу ландшафта" << std::endl;
                        return;
                    }
                }
            }
            if(answer == "R"){
                if(field->map1[x][y+1]->type == "landscape"){
                    if(field->getLand()->isMoved(field->map1[x][y]))
                        if(field->getLand()->isDamage(field->map1[x][y])){
                            field->map1[x][y]->health -= 3;
                            std::cout << "! Воин получил урон в размере 3 едениц !" << std::endl;
                            field->moveUnite(field->map1[x][y], x, y+1);
                            return;
                        }else {
                            field->moveUnite(field->map1[x][y], x, y+1);
                            return;
                        }
                    else{
                        std::cout << "Воин не может передвигаться по даннаму типу ландшафта" << std::endl;
                        return;
                    }
                }
            }
            if(answer == "U"){
                if(field->map1[x-1][y]->type == "landscape"){
                    if(field->getLand()->isMoved(field->map1[x][y]))
                        if(field->getLand()->isDamage(field->map1[x][y])){
                            field->map1[x][y]->health -= 3;
                            std::cout << "! Воин получил урон в размере 3 едениц !" << std::endl;
                            field->moveUnite(field->map1[x][y], x-1, y);
                            return;
                        }else {
                            field->moveUnite(field->map1[x][y], x-1, y);
                            return;
                        }
                    else{
                        std::cout << "Воин не может передвигаться по даннаму типу ландшафта" << std::endl;
                        return;
                    }
                }
            }
            if(answer == "D"){
                if(field->map1[x+1][y]->type == "landscape"){
                    if(field->getLand()->isMoved(field->map1[x][y])){
                        if(field->getLand()->isDamage(field->map1[x][y])){
                            field->map1[x][y]->health -= 3;
                            std::cout << "! Воин получил урон в размере 3 едениц !" << std::endl;
                            field->moveUnite(field->map1[x][y], x+1, y);
                            return;
                        }else {
                            //std::cout << field->map1[x][y]->x << ' ' << field->map1[x][y]->y << std::endl;
                            //std::cout << x << ' ' << y << std::endl;
                            field->moveUnite(field->map1[x][y], x+1, y);
                            return;
                        }
                    }
                    else{
                        std::cout << "Воин не может передвигаться по даннаму типу ландшафта" << std::endl;
                        return;
                    }
                }
            }
            std::cout << "Клетка игрового поля занята" << std::endl;
            return;
        }
    }

}

int Base::getCount(){
    return counter;
}
