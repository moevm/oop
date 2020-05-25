//
// Created by max on 31.03.20.
//

#include "UnitAction.h"

void UnitAction::services(Field* f,Unit *unit, NeutralObject *object,Interaction* inter, bool &check) {
    inter->services(f,unit,object,check);
}

void UnitAction::showCharacteristics(Field* f, Unit *curr_unit) {
    f->getLog()->write(curr_unit->getUnitType() + "\n");
    f->getLog()->write("Здоровье - " + to_string(curr_unit->getXp()) + " из " + to_string(curr_unit->getMaxXp()) + "\n");
    f->getLog()->write("Моряль - " + to_string(curr_unit->getMoral()) + " из " + to_string(curr_unit->getMaxMoral()) + "\n");
    f->getLog()->write("Броня - " + to_string(curr_unit->getArmour()) + " из " + to_string(curr_unit->getMaxArmour()) + "\n");
    f->getLog()->write("Атака - " + to_string(curr_unit->getAttack()) + " из " + to_string(curr_unit->getMaxAttack()) + "\n");
}

void UnitAction::attack(Field*f,Unit* curr_unit,bool &check,Interaction* inter){
    inter->attack(f,curr_unit,check, f->getUnitXCoordinateById(curr_unit->getNumberInArray()),f->getUnitYCoordinateById(curr_unit->getNumberInArray()));
}

void UnitAction::repair(Field* f,Base* base,bool &check, Interaction *inter) {
    inter->repair(f,base, check);
}

void UnitAction::run(bool &check,Field* f) {
    Interaction inter;
    int x,y;
    bool check_if_base = false;
    bool check_if_neutral_object = false;
    Unit* curr_unit;
    int index,player_move;
    cout << "Введите индекс юнита: ";
    cin >> index;
    index--;
    if(index >= f->getNumberOfUnits() || index < 0){
        f->getLog()->write("Таково юнита не существует!!!\n");
        return;
    }
    curr_unit = f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(index)].getUnit();
    while (1) {
        check_if_base = false;
        check_if_neutral_object = false;
        cout << "0 - Ввернуться на шаг назад\n";
        cout << "1 - просмотреть характеристики\n";
        cout << "2 - аттаковать\n";
        cout << "3 - переместиться\n";
        if(f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(index)].getIfOccupiedByBase() &&
        f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(index)].getBase()->getObjectId()
        == f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(index)].getUnit()->getId()){
            cout << "4 - починить базу\n";
            check_if_base = true;
        }
        if(f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(index)].getIfOccupiedByBuilding()) {
            cout << "5 - воспользоваться услагами " << f->getNeutralObjectName(f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(index)].getNeutralObject()->getObjectId());
            check_if_neutral_object = true;
        }
        cin >> player_move;
        switch (player_move) {
            case 0:
                f->getLog()->write("Опция вернуться назад\n");
                return;
            case 1:
                f->getLog()->write("Опция показать характеристики\n");
                this->showCharacteristics(f,curr_unit);
                break;
            case 2:
                this->attack(f,curr_unit,check,&inter);
                break;
            case 3:
                f->getLog()->write("Опция переместиться\n");
                cout << "Введите координаты, куда хотите переместить юнита\n";
                cin >> x >> y;
                f->move(f->getUnitXCoordinateById(index),f->getUnitYCoordinateById(index),x,y,check);
                break;
            case 4:
                if(check_if_base) {
                    f->getLog()->write("Опция починить базу\n");
                    this->repair(f,
                                 f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(index)].getBase(),
                                 check, &inter);
                    break;
                }
            case 5:
                if(check_if_neutral_object) {
                    f->getLog()->write("Опция воспользоваться услугами\n");
                    this->services(f, f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(
                            index)].getUnit(),
                                   f->field[f->getUnitXCoordinateById(index)][f->getUnitYCoordinateById(
                                           index)].getNeutralObject(), &inter, check);
                    break;
                }
        }
        if(check)
            return;
    }
}