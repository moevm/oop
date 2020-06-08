//
// Created by therealyou on 14.03.2020.
//

#ifndef LAB1_OBSERVER_H
#define LAB1_OBSERVER_H


class SubjectObserve;

class Observer {
public:
    virtual void update(SubjectObserve* subjectObserve) = 0;
};


#endif //LAB1_OBSERVER_H
