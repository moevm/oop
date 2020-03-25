#ifndef COMPONENT_H
#define COMPONENT_H

#include "unitfactory.h"

class ComponentKeeper
{
protected:
    ComponentKeeper *parent;
public:
    virtual ~ComponentKeeper() {}
    virtual ComponentKeeper *getParent() const;
    virtual void setParent(ComponentKeeper *value);
    virtual void addComponent(ComponentKeeper *component) {delete component;}
    virtual bool removeUnitComponent(Unit *unit) = 0;
    virtual size_t getLength() const = 0;
    virtual ComponentKeeper *getComponent(unsigned index) {return this;}
    virtual std::list<Unit *> getUnitList() = 0;
    virtual bool isComposite() {return false;}
};

class UnitKeeper : public ComponentKeeper
{
public:
    UnitKeeper(Unit *unit)
        :unit(unit) {}
    std::list<Unit *> getUnitList() {
        std::list<Unit *> unitList = {unit};
        return unitList;
    }
    bool removeUnitComponent(Unit *unit) {
        return this->unit == unit;
    }
    size_t getLength() const {return 1;}
private:
    Unit *unit;
};

class CompositeKeeper : public ComponentKeeper
{
public:
    bool isComposite() {
        return true;
    }
    void addComponent(ComponentKeeper *component);
    bool removeUnitComponent(Unit *unit);
    size_t getLength() const;
    ComponentKeeper *getComponent(unsigned index);
    std::list<Unit *> getUnitList();
protected:
    std::vector<ComponentKeeper *> children;
};

#endif // COMPONENT_H
