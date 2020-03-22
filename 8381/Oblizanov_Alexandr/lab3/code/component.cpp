#include "component.h"

ComponentKeeper *ComponentKeeper::getParent() const
{
    return parent;
}

void ComponentKeeper::setParent(ComponentKeeper *value)
{
    parent = value;
}


void CompositeKeeper::addComponent(ComponentKeeper *component)
{
    children.push_back(component);
}

bool CompositeKeeper::removeUnitComponent(Unit *unit)
{
    for (unsigned i=0; i<children.size(); i++)
    {
        if (children[i]->removeUnitComponent(unit))
        {
            children.erase(children.begin() + i);
            return true;
        }
    }
    return false;
}

size_t CompositeKeeper::getLength() const
{
    return children.size();
}

ComponentKeeper *CompositeKeeper::getComponent(unsigned index)
{
    if (index >= children.size())
        throw std::invalid_argument("index out of range");
    return children.at(index);
}

std::list<Unit *> CompositeKeeper::getUnitList()
{
    std::list <Unit *> unitList;
    for (unsigned i=0; i<children.size(); i++)
    {
        unitList.merge(children[i]->getUnitList());
    }
    return unitList;
}
