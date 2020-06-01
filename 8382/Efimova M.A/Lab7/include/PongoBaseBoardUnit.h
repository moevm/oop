#pragma once
#include "PlayableBoardUnit.h"
#include "BoardUnitFactory.h"
#include "User.h"
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
	PongoBaseBoardUnit(User* user);
	PongoBaseBoardUnit(QJsonObject snapshot, User* user, Board* board);
	void unitDeathHook(BoardUnit* dyingUnit);
	void unitCreatedHook();
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	std::vector<ActionMeta> turnAction() override;
	std::string getName() override;
	QJsonObject getSnapshot() override;
	BaseStats getBaseStats();
	User* getUser();
protected:
	std::map<std::string, BoardUnitFactory*> factories;
	BaseStats _baseStats;
	User* _user;
};

