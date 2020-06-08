//
// Created by therealyou on 14.03.2020.
//

#include "SubjectObserve.h"

void SubjectObserve::addObserver(Observer *observer) {
    observers.push_back(observer);
}

void SubjectObserve::removeObserver(Observer *observer) {
//    int i = observers.index
}

void SubjectObserve::notify() {
    for (Observer* observer : observers){
        observer->update(this);
    }
}
