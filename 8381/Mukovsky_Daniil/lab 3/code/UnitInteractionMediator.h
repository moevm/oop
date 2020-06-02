#pragma once
#include "Unit.h"


class UnitInteractionMediator
{
public:
	bool commitInteraction(Unit* attacker, FieldObject* defender, bool isAttack, bool curPlayer) {
		//if ((defender->getAbstractClass() != "Unit") || (defender->getAbstractClass != "Base")) return false;
		if (isAttack) {
			if (attacker->getTeam() != curPlayer) {
				std::cout << "Wrong attacker unit\n";
				return false;
			}
			if (defender->getTeam() == curPlayer) {
				std::cout << "Cant attack ally\n";
				return false;
			}
			if (!attacker->commitAttack(defender)) return false;
		}
		else {
			if (attacker->getShortName() != "B_t" && attacker->getShortName() != "B_d") {
				std::cout << "Only buffers can heal\n";
				return false;
			}
			if (attacker->getTeam() != curPlayer) {
				std::cout << "Wrong healer unit\n";
				return false;
			}
			if (defender->getTeam() != curPlayer) {
				std::cout << "Wrong target unit\n";
				return false;
			}
			if (!attacker->commitHeal(defender)) return false;
		}
		return true;
	}
};

