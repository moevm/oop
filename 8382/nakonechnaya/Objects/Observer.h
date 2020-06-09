#ifndef OOP_OBSERVER_H
#define OOP_OBSERVER_H
#include "Object.h"

class Observer : public Object{
public:
    virtual ~Observer(){};
    virtual void update(std::string newAction) = 0;
};
#endif //OOP_OBSERVER_H
