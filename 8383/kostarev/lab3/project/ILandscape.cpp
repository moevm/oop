#include "ILandscape.h"

Landscapes Hill::typeOfLandscape(){
	return HILL;
}

Landscapes Plain::typeOfLandscape() {
	return PLAIN;
}

Landscapes Lake::typeOfLandscape() {
	return LAKE;
}

Proxy::Proxy(ILandscape* l){
	landscape = l;
	type = landscape->typeOfLandscape();
}

bool Proxy::doSomething(IUnit* build){
	Builds name = build->typeOfBuild();
	if (type == LAKE) {
		if (name == VODOKANAL) {
			dynamic_cast<Building*>(build)->setWater(dynamic_cast<Building*>(build)->getWater() + 100);
			return true;
		}
		else{
			return false;
		}
	}
	else if (type == HILL) {
		if (name == POWERHOUSE) {
			dynamic_cast<Building*>(build)->setWater(dynamic_cast<Building*>(build)->getEnergy() + 100);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (name == VODOKANAL || name == POWERHOUSE) {
			return false;
		}
		return true;
	}
}

Landscapes Proxy::typeOfLandscape(){
	return type;
}

