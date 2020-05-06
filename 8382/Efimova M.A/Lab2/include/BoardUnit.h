#pragma once
#include <vector>
#include <string>
class BoardUnit
{
public:
	enum class UnitType{Pongo, Base, Terrain, Misc};
	struct ActionMeta {
		BoardUnit* fromUnit = nullptr;
		BoardUnit* toUnit = nullptr;

		bool isMove = false;
		unsigned int moveX = 0;
		unsigned int moveY = 0;

		bool isHeal = false;
		unsigned int hpHeal = 0;
		unsigned int armorBuff = 0;

		bool isAttack = false;
		unsigned int hpAttack = 0;
		unsigned int armorAttack = 0;

		bool isCreate = false;
		BoardUnit* createdUnit = nullptr;
		unsigned int unitX = 0;
		unsigned int unitY = 0;
	};
	BoardUnit();
	~BoardUnit();
	virtual BoardUnit* getCopy() = 0;
	virtual std::vector<ActionMeta> turnAction() = 0;
	//virtual UnitType getType() = 0;
	unsigned int getID();
	virtual std::string getName() = 0;
private:
	static unsigned int getUnitCount();
	static unsigned int unitCount;
	static unsigned int idCount;
	unsigned int _id;
};

