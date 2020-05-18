#pragma once
#include "PlayableBoardUnit.h"
#include "BoardUnitFactory.h"
#include <map>
class PongoBaseBoardUnit : public PlayableBoardUnit
{
public:
	struct BaseStats {
		int level = 0;
		int maxUnitCreationPerTurn = 0;
		int maxUnit = 0;
		int unitCount = 0;
		//ideally there will be one field for each unit type->subtype
	};
	PongoBaseBoardUnit();
	PongoBaseBoardUnit(QJsonObject snapshot, Board* board);
	void unitDeathHook(BoardUnit* dyingUnit);
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	std::vector<ActionMeta> turnAction() override;
	std::string getName() override;
	QJsonObject getSnapshot() override;
	BaseStats getBaseStats();
protected:
	std::map<std::string, BoardUnitFactory*> factories;
	BaseStats _baseStats;
};

