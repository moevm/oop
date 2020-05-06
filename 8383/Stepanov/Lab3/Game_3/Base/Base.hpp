//
//  Base.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Base_hpp
#define Base_hpp

#include <vector>

#include "Field.hpp"
#include "IObserver.hpp"
#include "Unit.hpp"

#include "ConcreteUnitRunner.hpp"
#include "ConcreteUnitShooter.hpp"
#include "ConcreteUnitSmoker.hpp"

#include "FlyweightUnitFactory.hpp"

#include "ConcreteHealthPound.hpp"
#include "ConcreteBoxWithArmor.hpp"
#include "ConcretePowerChemical.hpp"
#include "ConcreteWorkbenchForWeapons.hpp"

class Field;


class Base : public IObserver {
    
    Unit * units[9] = {nullptr};
    
    std::vector <Unit *> toDelet;
    FlyweightUnitFactory flyFactory;
    
    int numberUnit = 0;
    int countUnit = 0;
    int x = 0;
    int y = 0;
    int concretCountUnit[3] = {0, 0, 0};
    Field *field;
    char name[3];
    
    

    Unit* createUnit(int whatUnit, bool isProtected);   // функция создает юнита

public:
    
    ~Base ();
    
    void Update(Unit *unit) override;               // оповещание о том, что юнит умер


    char * getName ();                              // возвращает имя базы
    
    Base (int i, int x, int y, Field *field);
    bool setFirstUnits (Field *field);              // ставит юнитов на поле при старте
    bool setNeutralObjects (Field *field);          // ставит нейтральные объекты на поле при старте

    Unit* getUnit (int i);                          // возвращает юнита с индексом i из массива юнитов

    Unit* findUnit (std::string name);              // ищет юнита в массиве юнитов
    
         
    
    //++++++++++++++++++++++++++++++++++++++
    bool spawn (char typeOfUnit, bool isProtected);
    //++++++++++++++++++++++++++++++++++++++


};


#endif /* Base_hpp */
