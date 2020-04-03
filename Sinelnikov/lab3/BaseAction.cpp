//
// Created by max on 01.04.20.
//

#include "BaseAction.h"

void BaseAction::setBase(Field* f){
    Interaction inter;
    inter.setBase(f);
}

void BaseAction::showCharacteristics(Base* base) {
    cout << "ID :" << base->getObjectId() << "\n";
    cout  << "Здоровье " << base->getBaseXp() << " из " << base->getMaxXp() << "\n";
    cout << "Количество юнитов, принадлежащих базе: " << base->getNumberOfUnits() << "\n";
    cout << "Максимальное количество юнитов на базу: " << base->getMaxNumberOfUnits() << "\n";
    cout << "Положение базы: " << base->getXCoord() << " " << base->getYCoord() << "\n";
}

void BaseAction::run(Field* f, bool &check) {
    int player_move;
    int id;
    cout << "Введите id базы: ";
    cin >> id;
    id--;
    while (1) {
        if(id >= f->getNumberOfBases() || id < 0){
            cout << "Такой базы нет.На поле всего " << f->getNumberOfBases() << " баз\n";
            return;
        }
        cout << "0 - вернуться на предыдущий шаг\n";
        cout << "1 - показать характеристики\n";
        cout << "2 - создать юнита\n";
        cin >> player_move;
        switch (player_move){
            case 0:
                return;
            case 1:
                this->showCharacteristics(f->field[f->getBaseXCoordinateById(id)][f->getBaseYCoordinateById(id)].getBase());
                break;
            case 2:
                f->field[f->getBaseXCoordinateById(id)][f->getBaseYCoordinateById(id)].getBase()->createUnit(f,check);
                break;
        }
        if(check)
            return;
    }
}