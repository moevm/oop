#include "base.h"

Unit* Base::createUnit(int code, ArmyFactory& factory){
    Unit* unit;
    if (code == 0){
        unit = factory.createGladiator(x, y);
    }
    if (code == 1){
        unit = factory.createGunslinger(x, y);
    }
    if (code == 2){
        unit = factory.createHealer(x, y);
    }
    if (code == 3){
        unit = factory.createWizard(x, y);
    }
    if (code == 4){
        unit = factory.createJew(x, y);
    }
    if (code == 5){
        unit = factory.createKamikadze(x, y);
    }
    if (unit->cost <= this->gold)
    {
        this->gold -= unit->cost;
        countOfUnits++;
        return unit;
    }
    else{
        cout << "\nNot enough gold\n";
        delete unit;
        return nullptr;
    }
}
