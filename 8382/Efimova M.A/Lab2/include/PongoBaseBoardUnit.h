#pragma once
#include "PlayableBoardUnit.h"
#include "BoardUnitFactory.h"
#include <map>
class PongoBaseBoardUnit : public PlayableBoardUnit
{
public:
	struct BaseStats {
		unsigned int level = 0;
		unsigned int maxUnitCreationPerTurn = 0;
		unsigned int maxUnit = 0;
		//ideally there will be one field for each unit type->subtype
	};
	PongoBaseBoardUnit();
	void unitDeathHook(BoardUnit* dyingUnit);
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	std::vector<ActionMeta> turnAction() override;
	std::string getName() override;
	BoardUnit* getCopy() override;
	BaseStats getBaseStats();
protected:
	std::map<std::string, BoardUnitFactory*> factories;
	unsigned int unitCount = 0;
	BaseStats _baseStats;
};

