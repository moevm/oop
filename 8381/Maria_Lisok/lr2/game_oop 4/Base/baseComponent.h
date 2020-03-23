#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H
#include "unit.h"
class BaseComponent{
protected:
    BaseComponent* parent;
public:
    virtual ~BaseComponent()=default;
    BaseComponent *getParent() const;
    void setParent(BaseComponent *value);
    virtual void Add(BaseComponent *component);
    virtual void Remove(BaseComponent *component);
    virtual bool IsComposite() const;
    virtual string nameUnit(Unit *unit) = 0;
    virtual string characteristicUnit(Unit *unit) = 0;
};
#endif // BASECOMPONENT_H
