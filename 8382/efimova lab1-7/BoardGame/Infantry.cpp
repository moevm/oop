#include "Infantry.h"

Infantry::ActionMeta Infantry::turnAction() {
	ActionMeta meta;
	return meta;
}

Swordsman::Swordsman() {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

Swordsman::ActionMeta Swordsman::userAction() {
	ActionMeta meta;
	return meta;
}

Swordsman::ActionMeta Swordsman::defend(Swordsman::ActionMeta) {
	ActionMeta meta;
	return meta;
}

BoardUnit* Swordsman::getCopy() {
	auto man = new Swordsman();
	man->_stats = this->_stats;
	return man;
}

Spearman::Spearman() {
	_stats.health = 10;
	_stats.armor = 15;
	_stats.attack = 20;
}

Spearman::ActionMeta Spearman::userAction() {
	ActionMeta meta;
	return meta;
}

Spearman::ActionMeta Spearman::defend(Spearman::ActionMeta) {
	ActionMeta meta;
	return meta;
}

BoardUnit* Spearman::getCopy() {
	auto man = new Spearman();
	man->_stats = this->_stats;
	return man;
}

BoardUnit* InfantryFactory::getType(int type) { //фабрика
	switch (type) //если 0, то одни, если 1,  то другие
	{
	case 0:
		return (BoardUnit*)(new Swordsman());
		break;
	case 1:
		return (BoardUnit*)(new Spearman());
		break;
	default:
		//throw
		return nullptr;
		break;
	}
}

