#include "pch.h"
#include "GameUnits.h"
#include "GameUtilities.h"
#include "GameField.h"
#include <iostream>
#include <fstream>



void GameUnits::updateBorders(Vector2D fieldBorders) {
	borders = fieldBorders;
	for (auto &unit : units) {
		unit->updateLocation(fieldBorders);
	}
}

void GameUnits::switchUnit(bool forward) {
	units[currentUnitIndex]->unitProps.isActive = false;
	if (forward) {
		currentUnitIndex++;
	} else {
		currentUnitIndex--;
	}
	GameUtilities::clamp(currentUnitIndex, units.size() - 1, 0);
	units[currentUnitIndex]->unitProps.isActive = true;

}

bool GameUnits::createUnit(char type, Vector2D location) {
	if (units.size() < UNITS_MAX) {
		switch (type) {
		case UNIT_L_BEE:
			units.push_back(unitsFactoryLigth.createFlyingUnit());
			break;
		case UNIT_L_FLOWER:
			units.push_back(unitsFactoryLigth.createGroundUnit());
			break;
		case UNIT_L_SPRINKLER:
			units.push_back(unitsFactoryLigth.createSmallUnit());
			break;
		case UNIT_D_FLY:
			units.push_back(unitsFactoryDew.createFlyingUnit());
			break;
		case UNIT_D_COAL:
			units.push_back(unitsFactoryDew.createGroundUnit());
			break;
		case UNIT_D_COLLECTOR:
			units.push_back(unitsFactoryDew.createSmallUnit());
			break;
		default:
			break;
		}

		units.back()->unitProps.location = location;
		GameUtilities::clamp(units.back()->unitProps.location, borders, Vector2D(0, 0));
		if (units.size() == 1) {
			currentUnitIndex = 0;
			units.back()->unitProps.isActive = true;
		}

		return true;
	}

	return false;
}

bool GameUnits::moveUnit(Vector2D direction) {
	if (!overlapCheck(units[currentUnitIndex]->unitProps.location + direction) && 
		field->getBlockAtLocation(units[currentUnitIndex]->unitProps.location + direction)->isWalkable) {
		units[currentUnitIndex]->move(direction, borders);

		field->onMove(*this);

		return true;
	}

	return false;
}

UnitParent *GameUnits::getUnit(Vector2D location) {
	for (auto &unit : units) {
		if (unit->unitProps.location == location) {
			return unit;
		}
	}

	return nullptr;
}

GameUnits::GameUnits(Vector2D fieldBorders, GameField *field) : field(field) {
	borders = fieldBorders;
}

GameUnits::GameUnits(std::string unitsFileName, Vector2D fieldBorders) {
	borders = fieldBorders;

	int size;
	char type;
	Vector2D location;
	std::ifstream ifs;
	ifs.open(unitsFileName, std::ifstream::in);
	ifs >> size;

	for (int i = 0; i < size; i++) {
		ifs >> type >> location.x >> location.y;
		createUnit(type, location);
	}

	units[0]->unitProps.isActive = true;
	currentUnitIndex = 0;

	ifs.close();


}

GameUnits::~GameUnits() {
	units.clear();
}

int GameUnits::overlapCheck(Vector2D targetLocation) {
	UnitParent *unit;
	unit = getUnit(targetLocation);
	if (unit != nullptr) return 1;

	return 0;
}

