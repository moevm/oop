//
// Created by kot on 08.05.2020.
//

#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer
{
public:
    virtual void update(Subject*)=0;
    virtual ~Observer()=default;
};

#endif //OBSERVER_H
