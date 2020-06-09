#include "base.h"

Base::Base(int x, int y, GField* field){
    this->field = field;
    if(field->map1[x][y] == nullptr && !flag_base){
        Unit* BASE = new Unit;
        BASE->x = x;
        BASE->y = y;
        BASE->health = 1000;
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
    if(field->map1[x][y] == nullptr){
        counter++;
        field->addUnit(unit, x, y);
    }
}

int Base::getCount(){
    return counter;
}
