#include "Grass.h"

bool Grass::isPassable() {
	return true;
}

BoardUnit* Grass::getCopy() {
	return new Grass();
}

std::vector<Grass::ActionMeta> Grass::turnAction() {
	std::vector<Grass::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}
