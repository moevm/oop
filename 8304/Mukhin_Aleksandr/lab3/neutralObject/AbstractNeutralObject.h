#ifndef LAB2_ABSTRACTNEUTRALOBJECT_H
#define LAB2_ABSTRACTNEUTRALOBJECT_H


#include "BaseComponent.h"

class AbstractNeutralObject : public BaseComponent {
public:
    virtual int get_health() const = 0;
    virtual int get_attack() const = 0;
    virtual int get_intelligence() const = 0;
    virtual void interaction() const = 0;
    virtual ~AbstractNeutralObject() {}
};


#endif
