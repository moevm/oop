#include "pch.h"
#include "GameBases.h"
#include "GameUtilities.h"
#include "GameField.h"


void GameBasesContainer::switchBase(bool forward) {
	bases[currentBaseIndex]->isActive = false;
	if (forward) {
		currentBaseIndex++;
	} else {
		currentBaseIndex--;
	}

	GameUtilities::clamp(currentBaseIndex, bases.size() - 1, 0);
	bases[currentBaseIndex]->isActive = true;
}

void GameBasesContainer::spawnUnit(int type) {
	switch (type) {
	case '1':
		bases[currentBaseIndex]->spawnCollector();
		break;
	case '2':
		bases[currentBaseIndex]->spawnSprinkler();
		break;
	case '3':
		bases[currentBaseIndex]->spawnU1();
		break;
	case '4':
		bases[currentBaseIndex]->spawnU2();
		break;
	case '5':
		bases[currentBaseIndex]->spawnU3();
		break;
	default:
		break;
	}
}

GameBase *GameBasesContainer::getBaseAtLocation(Vector2D loc) {
	for (auto &base : bases) {
		if (base->location == loc) return base;
	}
	return nullptr;
}

GameBasesContainer::GameBasesContainer(GameField &field, GameUnits &units) {
	bases.push_back(new DefaultBase(&units));
	bases.back()->location.x = field.fieldProps.dimensions.x / 2;
	bases.back()->location.y = field.fieldProps.dimensions.y - 1;
	bases.back()->isActive = true;
	currentBaseIndex = 0;
}


GameBasesContainer::~GameBasesContainer() {
}

GameBase::~GameBase() {
}

GameBase::GameBase() {
	baseUnits.resize(2); 
	baseUnits[0]->setSize(2);
	baseUnits[1]->setSize(3);
}

GameBase::GameBase(GameUnits *units){
	this->units = units;
	baseUnits.resize(2);
	for (auto &units : baseUnits) {
		units = new CompositeUnit;
	}
	baseUnits[0]->setSize(2);
	baseUnits[1]->setSize(3);
}

void GameBase::spawnU1() {
	if (baseUnits[1]->units[0] == nullptr) {
		baseUnits[1]->units[0] = spawnUnit(unitType01);
	}
}

void GameBase::spawnU2() {
	if (baseUnits[1]->units[1] == nullptr) {
		baseUnits[1]->units[1] = spawnUnit(unitType02);
	}
}

void GameBase::spawnU3() {
	if (baseUnits[1]->units[2] == nullptr) {
		baseUnits[1]->units[2] = spawnUnit(unitType03);
	}
}

void GameBase::spawnCollector() {
	if (baseUnits[0]->units[0] == nullptr) {
		if (units->createUnit(UNIT_D_COLLECTOR, Vector2D(location.x - 1, location.y - 1))) {
			baseUnits[0]->units[0] = units->units.back();
		}
	}
}

void GameBase::spawnSprinkler() {
	if (baseUnits[0]->units[1] == nullptr) {
		if (units->createUnit(UNIT_L_SPRINKLER, Vector2D(location.x - 1, location.y - 1))) {
			baseUnits[0]->units[1] = units->units.back();
		}
	}
}

void GameBase::updateAtributes() {
	for (auto &units : baseUnits) {
		units->update();
	}
}

UnitParent *GameBase::spawnUnit(char type) {
	if (units->createUnit(type, Vector2D(location.x - 1, location.y - 1))) {
		return units->units.back();
	}

	return nullptr;
}
