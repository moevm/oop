#include "PongoBaseBoardUnit.h"
#include "Artillery.h"
#include "Cavalry.h"
#include "Infantry.h"
#include "Game.h"

PongoBaseBoardUnit::PongoBaseBoardUnit() {
	auto artilleryFactory = new ArtilleryFactory(this);
	auto cavalryFactory = new CavalryFactory(this);
	auto infantryFactory = new InfantryFactory(this);
	factories.insert(std::pair<std::string, BoardUnitFactory*>("artillery", artilleryFactory));
	factories.insert(std::pair<std::string, BoardUnitFactory*>("infantry", infantryFactory));
	factories.insert(std::pair<std::string, BoardUnitFactory*>("cavalry", cavalryFactory));
}

PongoBaseBoardUnit::BaseStats PongoBaseBoardUnit::getBaseStats() {
	return _baseStats;
}

std::vector<PongoBaseBoardUnit::ActionMeta> PongoBaseBoardUnit::userAction(Board::BoardCell targetCell, int action) {
	std::vector<PongoBaseBoardUnit::ActionMeta> actionVec;
	ActionMeta meta;
	meta.isCreate = true;
	auto newUnit = factories.at("cavalry")->createUnit();
	meta.createdUnit = newUnit;
	auto coords = Game::getInstance()->getBoard()->getUnitCoords(targetCell.terrainUnit);
	meta.unitX = coords.first;
	meta.unitY = coords.second;
	actionVec.push_back(meta);
	return actionVec;
	//unit creation
}

std::vector<PongoBaseBoardUnit::ActionMeta> PongoBaseBoardUnit::defend(PongoBaseBoardUnit::ActionMeta) {
	std::vector<PongoBaseBoardUnit::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
	//unit creation
}

std::vector<PongoBaseBoardUnit::ActionMeta> PongoBaseBoardUnit::turnAction() {
	std::vector<PongoBaseBoardUnit::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
	//unit creation
}

void PongoBaseBoardUnit::unitDeathHook(BoardUnit* dyingUnit) {
	//death of unit notification
}

std::string PongoBaseBoardUnit::getName() {
	return "base";
}

BoardUnit* PongoBaseBoardUnit::getCopy() {
	return new PongoBaseBoardUnit();
}