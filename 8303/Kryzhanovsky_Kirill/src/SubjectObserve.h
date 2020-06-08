//
// Created by therealyou on 14.03.2020.
//

#ifndef LAB1_SUBJECTOBSERVE_H
#define LAB1_SUBJECTOBSERVE_H


#include <vector>
#include "Observer.h"

class SubjectObserve {
public:
    std::vector<Observer*> observers;
    void addObserver(Observer* observer);

    void notify();

    void removeObserver(Observer* observer);
};


#endif //LAB1_SUBJECTOBSERVE_H
