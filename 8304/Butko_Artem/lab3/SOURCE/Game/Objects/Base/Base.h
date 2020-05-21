//
// Created by Artem Butko on 15/05/2020.
//

#ifndef OOP_NEW_BASE_H
#define OOP_NEW_BASE_H

#include <map>
#include "../Object.h"
#include "Observer/IObserver.h"
#include "../../Factories/ObjectFactory/ObjectFactory.h"
#include "../../GameField/Field/Field.h"
#include "../Units/UnitComposite/UnitComposite.h"

/* Base -- класс базы.
 * --------------- ФУНКЦИИ --------------------
 * createUnit -- создать юнита на базе
 * getInformation -- информация о юнитах на базе,
 * наблюдение за юнитами на поле.
 * getUnit -- "забрать" юнита с базы на поле.
 * update -- обновить информацию для субъекта наблюдения.
 * ---------------------------------------------
 * unitsOnBase -- юниты на базе.
 * unitsOnField -- юниты, выпущенные с базы.
 * unitFactory -- абстрактная фабрика объектов для
 * создания юнитов
 * unitLimit -- лимит юнитов для хранения на базе.
 * unitCount, unitDead -- счетчики для юнитов на
 * базе и поле соответственно.
 */



class Field;

class Base : public Object, public IObserver
{
public:
    Base(Field* field, int x, int y, int unitLimit);

    int createUnit(char id);
    void getInformation();
    IUnit* getUnit(char id);
    void update(Subject* subject) override ;
private:
    std::map<char, int> unitsOnBase;
    UnitComposite unitsOnField;
    ObjectFactory unitFactory;
    Field* field;
    int x, y;
    int unitLimit;
    int unitCount;
    int unitDead;
};


#endif //OOP_NEW_BASE_H
