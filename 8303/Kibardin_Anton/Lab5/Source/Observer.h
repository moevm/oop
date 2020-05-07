//
// Created by anton on 15.03.2020.
//

#ifndef OOP_1_OBSERVER_H
#define OOP_1_OBSERVER_H

#include "Subject.h"

class Subject;

class Observer {
public:
    virtual void update(Subject* subject) = 0;

};


#endif //OOP_1_OBSERVER_H
