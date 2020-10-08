#include "base.h"

Base::Base (int maxUnitsCount, int health,
			int xx, int yy, int baseNumb)
			: baseNumb(baseNumb), unitCount(0),
			maxCount(maxUnitsCount), unitCurr(0),
			health(health), x(xx), y(yy)
{
	units = new Composite;
	units->add(new Composite);
	units->add(new Composite);
	units->add(new Composite);
	for (auto i = 0; i < 3; i++)
	{
		units->getChildren(i)->add(new Leaf);
		units->getChildren(i)->add(new Leaf);
	}
}

std::string Base::shortName()
{
    return  "ⒷⒶⓈⒺ";
}

int Base::getBaseNumb () const {
	return baseNumb;
}

int Base::getX () const {
	return x;
}

int Base::getY () const {
	return y;
}

int Base::getUnitCount () const {
	return unitCount;
}

int Base::getMaxCount () const {
	return maxCount;
}

int Base::getHealth () const {
	return health;
}

Unit *Base::createUnit (std::string unitName) {
	Unit* unit = nullptr;
	if (unitCount++ > maxCount)
	{
		std::cout << "max limit reached\n";
		return nullptr;
	}

	if (unitName == "Knight")
		unit = radiantFactory->createMelee();
	else if (unitName == "Dragon")
		unit = radiantFactory->createRange();
	else if (unitName == "Dryad")
		unit = radiantFactory->createSupport();
	else if (unitName == "Ork")
		unit = direFactory->createMelee();
	else if (unitName == "Chimera")
		unit = direFactory->createRange();
	else if (unitName == "Witch")
		unit = direFactory->createSupport();

	addUnit(unit);

	return unit;
}

void Base::addUnit (Unit *u) {
	auto unitName = u->getName();
	if (unitCount++ > maxCount)
	{
		std::cout << "max limit reached\n";
		throw std::range_error ("limit of units reached");
	}
	if (unitName == "Knight")
		units->getChildren(0)->getChildren(0)->addUnit(u);
	else if (unitName == "Dragon")
		units->getChildren(1)->getChildren(0)->addUnit(u);
	else if (unitName == "Dryad")
		units->getChildren(2)->getChildren(0)->addUnit(u);
	else if (unitName == "Orkk")
		units->getChildren(0)->getChildren(1)->addUnit(u);
	else if (unitName == "Chimera")
		units->getChildren(1)->getChildren(1)->addUnit(u);
	else if (unitName == "Witch")
		units->getChildren(2)->getChildren(1)->addUnit(u);
	unitCount++;


}

void Base::delUnit (Unit *u) {
	auto unitName = u->getName();
	if (unitName == "Knight")
		units->getChildren(0)->getChildren(0)->removeUnit(u);
	else if (unitName == "Dragon")
		units->getChildren(1)->getChildren(0)->removeUnit(u);
	else if (unitName == "Dryad")
		units->getChildren(2)->getChildren(0)->removeUnit(u);
	else if (unitName == "Orkk")
		units->getChildren(0)->getChildren(1)->removeUnit(u);
	else if (unitName == "Chimera")
		units->getChildren(1)->getChildren(1)->removeUnit(u);
	else if (unitName == "Witch")
		units->getChildren(2)->getChildren(1)->removeUnit(u);
	unitCount--;
	std::cout << "\nunit deleted\n";

}

//Unit *Base::getCurrUnit () {
//	return nullptr;
//}

bool Base::getDamage (int numb) {
	this->health -= numb;
	if (this->health <= 0){
		this->health = 0;
		return true;
	}
	return false;
}

std::string Base::printUnits ()
{
	return units->getUnits();
}

//void Base::delUnit (Subject *u) {
//
//}
