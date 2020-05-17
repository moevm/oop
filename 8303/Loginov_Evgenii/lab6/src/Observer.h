//
// Created by Evgeniy on 3/8/2020.
//

#ifndef OBSERVER
#define OBSERVER


class SubjectObserve;

class Observer {
public:
    virtual void update(SubjectObserve* subject) = 0;
};


#endif OBSERVER
