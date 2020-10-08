#ifndef COMPOSITE_H
#define COMPOSITE_H
#include <vector>
#include <list>
#include "../Units/unit.h"

class Component{
protected:
	Component *parent;
public:
	virtual ~Component() = default;
	void setParent(Component* parent)
	{
		this->parent = parent;
	}
	Component* hetParent() const
	{
		return this->parent;
	}
	virtual std::string getUnits() = 0;
	virtual void add(Component*) = 0;
	virtual void remove(Component*) = 0;
	virtual Component* getChildren(unsigned) = 0;
	virtual void addUnit(Unit*) = 0;
	virtual void removeUnit(Unit*) = 0;
};

class Composite : public Component
{
protected:
	std::vector<Component*> children;
public:
	std::string getUnits()
	{
		std::string out;
		out += "{";
		for (auto i : children) {
			out += i->getUnits();
		}
		out += "}";
		return out;
	}
	Component* getChildren(unsigned index)
	{
		if (index >= children.size())
			return nullptr; //size error
		return children[index];
	}
	void add(Component* comp)
	{
		children.push_back(comp);
		comp->setParent(this);
	}
	void remove(Component* comp)
	{
		for (auto i = 0; i < children.size(); i++)
			if (children[i] == comp)
				children.erase(children.begin() + i);
		comp->setParent(nullptr);
	}
	void addUnit(Unit* unit) {}
	void removeUnit(Unit* unit) {}
};

class Leaf : public Component {
protected:
	std::list<Unit *> units;
public:
	std::string getUnits ()
	{
		std::string out;
		out += "{";
		for (auto i : units) {
			out += i->getName() ;
		}
		out += "}";
		return out;
	}
	void addUnit(Unit* unit)
	{
		units.push_back(unit);
	}
	void removeUnit(Unit* unit)
	{
		units.remove(unit);

	}
	Component * getChildren(unsigned int index) {
		return this;
	}
//	std::list<Unit*> getUnits()
//	{
//		return units;
//	}

	void add(Component *component) {}
	void remove(Component *component) {}


};



#endif //COMPOSITE_H
