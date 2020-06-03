#include "PongoBaseBoardUnit.h"

PongoBaseBoardUnit::PongoBaseBoardUnit() {

}

PongoBaseBoardUnit::BaseStats PongoBaseBoardUnit::getBaseStats() {
	return _baseStats;
}

std::vector<PongoBaseBoardUnit::ActionMeta> PongoBaseBoardUnit::userAction() {
	std::vector<PongoBaseBoardUnit::ActionMeta> actionVec;
	ActionMeta meta;
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
