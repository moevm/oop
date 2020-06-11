//
// Created by anton on 15.03.2020.
//

#ifndef OOP_1_SUBJECT_H
#define OOP_1_SUBJECT_H


#include <vector>
#include "Observer.h"

class Observer;

class Subject {
public:
    std::vector<Observer*> observers;

    void addObserver(Observer*);

    void deleteObserver(Observer*);

    void notify();
};


#endif //OOP_1_SUBJECT_H
