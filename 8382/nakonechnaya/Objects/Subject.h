#ifndef OOP_SUBJECT_H
#define OOP_SUBJECT_H
#include "Object.h"
#include "Observer.h"

class Subject : public Object{
public:
    virtual ~Subject(){};
    virtual void addObservers(Observer *observer) = 0;
    virtual void notifyObservers(std::string *newAction) = 0;
};
#endif //OOP_SUBJECT_H
