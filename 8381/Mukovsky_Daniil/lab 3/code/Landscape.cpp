#include "Landscape.h"


Mountains::Mountains() {
	name = "Mountains";
	shortName = "M";
	canMove = false;
}

bool Mountains::canHoldFieldObject(FieldObject* unit) const { return true; }


void Mountains::checkUnitRange(FieldObject* unit_) const {
	Unit* unit = dynamic_cast<Unit*>(unit_);
	if (!unit) return;
	if (unit->getShortName() == "W_t" || unit->getShortName() == "W_d" || unit->getShortName() == "B_t") {
		unit->getAttributes()->setRange(0);
	}
}

Landscape* Mountains::copy() {
	return new Mountains(*this);
}

std::string Mountains::info() {
	std::string out = "Class: Mountains\n";
	return out;
}

Ground::Ground() {
	name = "Ground";
	shortName = "G";
	canMove = false;
}
bool Ground::canHoldFieldObject(FieldObject* unit) const{ return true; }

void Ground::checkUnitRange(FieldObject* unit_) const {
	Unit* unit = dynamic_cast<Unit*>(unit_);
	if (!unit) return;
	if (unit->getShortName() == "W_t" || unit->getShortName() == "W_d" || unit->getShortName() == "B_t") {
		unit->getAttributes()->setRange(1);
	}
}

Landscape* Ground::copy() {
	return new Ground(*this);
}

std::string Ground::info() {
	std::string out = "Class: Ground\n";
	return out;
}


Water::Water() {
	name = "Water";
	shortName = "W";
	canMove = false;
}

bool Water::canHoldFieldObject(FieldObject* object) const{
	if (object && object->getAbstractClass() == "Unit") {
		std::cout << "Unit can't swim\n";
		object->setAlive(false);
	}
	return false; 
}
void Water::checkUnitRange(FieldObject* unit_) const {
	Unit* unit = dynamic_cast<Unit*>(unit_);
	if (!unit) return;
	if (unit->getShortName() == "W_t" || unit->getShortName() == "W_d" || unit->getShortName() == "B_t") {
		unit->getAttributes()->setRange(1);
	}
}
Landscape* Water::copy(){
	return new Water(*this);
}
std::string Water::info() {
	std::string out = "Class: Water\n";
	return out;
}
