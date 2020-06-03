#pragma once
#include "PlayableBoardUnit.h"
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
	std::vector<ActionMeta> userAction() override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	std::vector<ActionMeta> turnAction() override;
	//UnitType getType() override;
	BaseStats getBaseStats();
protected:
	unsigned int unitCount = 0;
	BaseStats _baseStats;
};

