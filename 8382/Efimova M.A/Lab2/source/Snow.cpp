#include "Snow.h"

bool Snow::isPassable() {
	return true;
}

BoardUnit* Snow::getCopy() {
	return new Snow();
}

std::vector<Snow::ActionMeta> Snow::turnAction() {
	std::vector<Snow::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::string Snow::getName() {
	return "snow";
}
