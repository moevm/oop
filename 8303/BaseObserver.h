//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_BASEOBSERVER_H
#define OOP_LAB1_BASEOBSERVER_H

class BaseObserver {

public:
    virtual void onBaseNewUnitCreated(Unit *unit, Point position)=0;

};


#endif //OOP_LAB1_BASEOBSERVER_H
