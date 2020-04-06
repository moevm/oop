#include "pch.h"
#include "Commands.h"
#include "GameBases.h"
#include "GameUnits.h"

MoveUnitCommand::~MoveUnitCommand() {
	delete unitsContainer;
}

void MoveUnitCommand::execute() {
	unitsContainer->moveUnit(direction);
}

NextUnitCommand::~NextUnitCommand() {
	delete unitsContainer;
}

void NextUnitCommand::execute() {
	unitsContainer->switchUnit(isNext);
}

NextBaseCommand::~NextBaseCommand() {
	delete baseContainer;
}

void NextBaseCommand::execute() {
	baseContainer->switchBase(isNext);
}

SpawnUnitCommand::~SpawnUnitCommand() {
	delete baseContainer;
}

void SpawnUnitCommand::execute() {
	baseContainer->spawnUnit(type);
}

ActionUnitCommand::~ActionUnitCommand() {
	delete unitsContainer;
}

void ActionUnitCommand::execute() {
	unitsContainer->units[unitsContainer->currentUnitIndex]->attack();
}

BaseCommands::~BaseCommands() {
	delete baseContainer;
}

UnitCommands::~UnitCommands() {
	delete unitsContainer;
}
