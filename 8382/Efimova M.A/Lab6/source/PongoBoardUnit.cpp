#include "PongoBoardUnit.h"
#include "Game.h"

int PongoBoardUnit::unit_count = 0;

PongoBoardUnit::PongoBoardUnit(PongoBaseBoardUnit* base) : _base(base) {
	unit_count++;
}

PongoBoardUnit::PongoBoardUnit(QJsonObject snapshot, PongoBaseBoardUnit* base) : _base(base) {
	auto stats = snapshot["stats"].toObject();
	_stats.health = stats["health"].toInt();
	_stats.armor = stats["armor"].toInt();
	_stats.attack = stats["attack"].toInt();
	unit_count++;
}

PongoBoardUnit::~PongoBoardUnit() {
	unit_count--;
}

int PongoBoardUnit::getUnitCount() {
	return unit_count;
}

QJsonObject PongoBoardUnit::getSnapshot() {
	QJsonObject pongoUnitSnapshot;

	auto baseCoord = Game::getInstance()->getBoard()->getUnitCoords((BoardUnit*)_base);

	QJsonObject base;
	base.insert("x", baseCoord.first);
	base.insert("y", baseCoord.second);

	QJsonObject unitStats;
	unitStats.insert("health", _stats.health);
	unitStats.insert("armor", _stats.armor);
	unitStats.insert("attack", _stats.attack);
	pongoUnitSnapshot.insert("stats", unitStats);
	pongoUnitSnapshot.insert("type", "playableUnit");
	pongoUnitSnapshot.insert("class", getClassName().c_str());
	pongoUnitSnapshot.insert("subtype", getName().c_str());
	pongoUnitSnapshot.insert("snapshot", pongoUnitSnapshot);
	pongoUnitSnapshot.insert("base", base);
	return pongoUnitSnapshot;
}
