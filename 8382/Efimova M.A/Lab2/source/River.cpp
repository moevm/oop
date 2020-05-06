#include "River.h"

bool River::isPassable() {
	return true;
}

BoardUnit* River::getCopy() {
	return new River();
}

std::vector<River::ActionMeta> River::turnAction() {
	std::vector<River::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::string River::getName() {
	return "river";
}
