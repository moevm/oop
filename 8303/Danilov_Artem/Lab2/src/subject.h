//
// Created by kot on 08.05.2020.
//

#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"


class Subject
{
protected:
    std::vector<Observer*> listObserver;
public:
    void attach(Observer*);
    void detach(Observer*);
    void notify();

};


#endif //SUBJECT_H
