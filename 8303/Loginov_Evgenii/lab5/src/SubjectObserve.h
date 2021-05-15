//
// Created by Evgeniy on 3/8/2020.
//

#ifndef SUBJECTOBSERVER
#define SUBJECTOBSERVER


#include <vector>
#include "Observer.h"

class SubjectObserve{
public:
    std::vector<Observer*> masObserver;
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notify();

};

#endif SUBJECTOBSERVER
