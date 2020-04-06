#include "pch.h"
#include "NeutralObject.h"
#include "GameUnits.h"
#include <fstream>
#include <iostream>


NeutralObject::NeutralObject() {
}


NeutralObject::~NeutralObject() {
}

NeutralObjectContainer::NeutralObjectContainer(std::string fileName) {
	std::ifstream ifs;
	ifs.open(fileName, std::ifstream::in);
	int size;
	ifs >> size;

	int type;
	int x;
	int y;
	for (int i = 0; i < size; i++) {
		ifs >> type;
		switch (type) {
		case NeutralObjects::Apple:
			objects.push_back(new AppleObject);
			break;
		case NeutralObjects::Branch:
			objects.push_back(new BranchObject);
			break;
		case NeutralObjects::Dew:
			objects.push_back(new DewObject);
			break;
		case NeutralObjects::Ligth:
			objects.push_back(new LigthObject);
			break;
		default:
			break;
		}
		ifs >> x >> y;
		objects.back()->location = Vector2D(x, y);
	}
}

NeutralObject *NeutralObjectContainer::getObjectAtLocation(Vector2D loc) {
	for (auto &obj : objects) {
		if (obj->location == loc) return obj;
	}
	return nullptr;
}

void NeutralObjectContainer::useObject(GameUnits &units) {
	object->onExecute(units);
	for (size_t i = 0; i < objects.size(); i++) {
		if (object == objects[i]) {
			objects.erase(objects.begin() + i);
			return;
		}
	}
}

NeutralObjectContainer::~NeutralObjectContainer() {
	objects.clear();
	delete object;
}

bool NeutralObjectContainer::operator==(const GameUnits &units) {
	object = getObjectAtLocation(units.units[units.currentUnitIndex]->unitProps.location);
	if (object != nullptr) {
		return true;
	}

	return false;
}

void AppleObject::onExecute(GameUnits &units) {
	std::cout << "It's APPLE" << std::endl;
}

void DewObject::onExecute(GameUnits &units) {
	std::cout << "It's DEW" << std::endl;
}

void LigthObject::onExecute(GameUnits &units) {
	std::cout << "It's LIGTH" << std::endl;
}

void BranchObject::onExecute(GameUnits &units) {
	std::cout << "It's BRANCH" << std::endl;
}
