#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Subject
{
public:
    std::vector < class Observer * > views;
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notify();
};

class Observer
{
public:
    virtual void update(Subject* subject) = 0;
    ~Observer(){}
};

#endif // OBSERVER_H
