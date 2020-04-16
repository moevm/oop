//
//  Base.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Base.hpp"



    Unit* Base::createUnit(int whatUnit, bool isProtected) {

        ConcreteUnitShooter sho;
        ConcreteUnitRunner run;
        ConcreteUnitSmoker smo;

        concretCountUnit[whatUnit] += 2;

        Unit *u = nullptr;

        if (whatUnit == 0) u = smo.CreateUnit(concretCountUnit[whatUnit]+'0', isProtected);

        else if (whatUnit == 1) u  = sho.CreateUnit(concretCountUnit[whatUnit]+'0', isProtected);

        else if (whatUnit == 2) u = run.CreateUnit(concretCountUnit[whatUnit]+'0', isProtected);

        else return nullptr;

        u->uid = flyFactory.getUnitID(whatUnit);
        
          

        return u;

    }

    
    Base::~Base () {

        for (int i = 0; i < toDelet.size(); i++){
            delete toDelet[i];
        }
        
        
        for (int i = 0; i < 9; i++){
            if (units[i]) {
                delete units[i];
            }
        }
    }

//    ++++++++++++++++++++++++++++++++++++++
    
    
    void Base::Update(Unit *unit) {
        std::cout << unit->getName() << " Killed" << std::endl;

        field->setUnit(nullptr, unit->getX(), unit->getY());

        for (int i = 0; i < 9; i++){

            if (units[i] == unit) {
                units[i] = nullptr;
                break;
            }
        }

        toDelet.push_back(unit);
        countUnit--;

    }

    
    char * Base::getName () {
        return name;
    }
    
    
    Base::Base (int i, int x, int y, Field *field) {
        this->x = x;
        this->y = y;
        concretCountUnit[0] = i - 2;
        concretCountUnit[1] = i - 2;
        concretCountUnit[2] = i - 2;
        
        name[0] = 'B';
        name[2] = '\0';
        
        if (x > y) {
            name[1] = '1';
        } else {
            name[1] = '2';
        }
        
        this->field = field;
        field->setBase(this->name, x, y);
            
    }
    
    bool Base::setFirstUnits (Field *field) {

        int arr[6] = {0, 1, 1, 2, 2, 2};

        for (int i = 0; i < 6; i++) {

            units[i] = createUnit(arr[i], true);

            units[i]->Attach(this);


        }

        if (x > y) {

            units[0]->setXY(x-1, 1);
            units[1]->setXY(x-2, 0);
            units[2]->setXY(x  , 2);
            units[3]->setXY(x-1, 3);
            units[4]->setXY(x-2, 2);
            units[5]->setXY(x-3, 1);



        } else {


            units[0]->setXY(1, y-1);
            units[1]->setXY(0, y-2);
            units[2]->setXY(2, y);
            units[3]->setXY(3, y-1);
            units[4]->setXY(2, y-2);
            units[5]->setXY(1, y-3);


        }

        for (int i = 0; i < 6; i++)
        field->setUnit(units[i], units[i]->getX(), units[i]->getY());

        countUnit = 6;





        return true;

    }

    Unit* Base::getUnit (int i) {

        return units[i];
    }

    Unit* Base::findUnit (std::string name){

        for (int i = 0; i < 9; i++) {

            if (units[i] && units[i]->name[0] == name[0] && units[i]->name[1] == name[1]) {
                return units[i];
            }

        }

         return nullptr;
    }


bool Base::setNeutralObjects (Field *field){
    
    ConcreteHealthPound hp;
    ConcreteBoxWithArmor ba;
    ConcretePowerChemical pc;
    ConcreteWorkbenchForWeapons ww;
    
    //field->setNeutralObject(hp.CreateNeutralObject(), 0, 0);
    
    if (y > x) {
        
        field->setNeutralObject(hp.CreateNeutralObject(), 0, 1);
        field->setNeutralObject(ba.CreateNeutralObject(), y, y-1);
         
        if ((y+1) % 2 == 0){
            field->setNeutralObject(pc.CreateNeutralObject(), (y+1)/2-1,(y+1)/2);
            field->setNeutralObject(ww.CreateNeutralObject(), (y+1)/2,(y+1)/2);

        } else {
            field->setNeutralObject(pc.CreateNeutralObject(), y/2-1,y/2);
            field->setNeutralObject(ww.CreateNeutralObject(), y/2,y/2+1);

        }
        
        
    } else {
        field->setNeutralObject(hp.CreateNeutralObject(), x-1, x);
        field->setNeutralObject(ba.CreateNeutralObject(), 1, 0);
         
        if ((x+1) % 2 == 0){
            field->setNeutralObject(ww.CreateNeutralObject(), (x+1)/2-1,(x+1)/2-1);
            field->setNeutralObject(pc.CreateNeutralObject(), (x+1)/2,(x+1)/2-1);

        } else {
            field->setNeutralObject(pc.CreateNeutralObject(), x/2+1,x/2);
            field->setNeutralObject(ww.CreateNeutralObject(), x/2,x/2-1);
        }
    }
    
    return true;
}


bool Base::spawn (char typeOfUnit, bool isProtected){
    
    int whatInCell;
    int spawnX, spawnY;
    int numOfUnit = 0;
    
    if (countUnit >= 9){
        std::cout << "Count of units is max" << std::endl;
        return false;
    }
    
    switch (typeOfUnit) {
        case '!':
            numOfUnit = 2;
            break;
        case '<':
            numOfUnit = 1;
            break;
        case '>':
            numOfUnit = 1;
            break;
        case '$':
            std::cout << "You can't spawn unit Smoker"<< std::endl;
            return false;
            break;
        default:
            std::cout << "Wrong type of unit" << std::endl;
            return false;
            break;
    }
    
    if (x > y){
        spawnX = x-1;
        spawnY = y+1;
    } else {
        spawnX = x+1;
        spawnY = y-1;
    }
    
    whatInCell = field->whatInCell(spawnX, spawnY);
    
    if (whatInCell == 4) {
        
        if (concretCountUnit[numOfUnit] + 2 >= 10) {
            std::cout << "max count this type of unit" << std::endl;
            return false;
        }
        
        for (int i = 0; i < 9; i++) {
            
            if (units[i] == nullptr) {
                units[i] = createUnit(numOfUnit, isProtected);
                units[i]->Attach(this);
                units[i]->setXY(spawnX, spawnY);
                field->setUnit(units[i], spawnX, spawnY);
                break;
            }
            
        }
    } else {
        std::cout << "Error spawn unit. Base: " << name << std::endl;
        return false;
    }
    
    
    
    return true;
}
