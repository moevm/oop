#include "Artillery.h"

Artillery::Artillery(PongoBaseBoardUnit* base) : PongoBoardUnit(base) {

}

std::vector<Artillery::ActionMeta> Artillery::turnAction() {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

Cannon::Cannon(PongoBaseBoardUnit* base) : Artillery(base) {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

std::vector<Cannon::ActionMeta> Cannon::userAction(Board::BoardCell targetCell, int action) {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::vector<Cannon::ActionMeta> Cannon::defend(Cannon::ActionMeta) {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

BoardUnit* Cannon::getCopy() {
	return nullptr;
}

std::string Cannon::getName() {
	return "cannon";
}

Catapult::Catapult(PongoBaseBoardUnit* base) : Artillery(base) {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

std::vector<Cannon::ActionMeta> Catapult::userAction(Board::BoardCell targetCell, int action) {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

std::vector<Cannon::ActionMeta> Catapult::defend(Catapult::ActionMeta) {
	std::vector<Cannon::ActionMeta> actionVec;
	ActionMeta meta;
	actionVec.push_back(meta);
	return actionVec;
}

BoardUnit* Catapult::getCopy() {
	return nullptr;
}

std::string Catapult::getName() {
	return "catapult";
}

PlayableBoardUnit* ArtilleryFactory::createUnit(int type) {
	switch (type)
	{
	case 0:
		return (PlayableBoardUnit*)(new Cannon(_base));
		break;
	case 1:
		return (PlayableBoardUnit*)(new Catapult(_base));
		break;
	default:
		//throw
		return nullptr;
		break;
	}
}