#pragma once
#include "GameUnits.h"
#include <vector>
#include <iostream>

class Vector2D;
class GameField;

enum GameBaseTypes {Zero, One, Two, Three, Four};

class GameBaseAtribute {
private:
	int val;
public:
	GameBaseAtribute() {
		val = 0;
	}

	void setVal(int val) {
		this->val = val;
	}

	int getVal() {
		return this->val;
	}

	void increaseVal(int increment) {
		val += increment;
	}
};


class GameBase {
protected:
	GameUnits *units;
public:
	GameBaseAtribute dew;
	GameBaseAtribute ligth;
	bool isActive = false;
	GameBaseTypes type;
	Vector2D location;
	std::vector<CompositeUnit*> baseUnits;
	char unitType01;
	char unitType02;
	char unitType03;

	~GameBase();
	GameBase();
	GameBase(GameUnits *units);

	virtual void spawnU1();
	virtual void spawnU2();
	virtual void spawnU3();
	void spawnCollector();
	void spawnSprinkler();

	void updateAtributes();

	UnitParent *spawnUnit(char type);
};

class DefaultBase : public GameBase {
public:
	DefaultBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::Zero;
		baseUnits[1]->setSize(1);
	}
	void spawnU1() {
		std::cout << "Not Rigth Now";
	};
	void spawnU2() {
		std::cout << "Not Rigth Now";
	};
	void spawnU3() {
		std::cout << "Not Rigth Now";
	};
};

class OneBase : public GameBase {
public:
	OneBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::One;
		unitType01 = UNIT_D_FLY;
		unitType02 = UNIT_L_BEE;
		unitType03 = UNIT_D_COAL;
	}
};

class TwoBase : public GameBase {
public:
	TwoBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::Two;
		unitType01 = UNIT_D_COAL;
		unitType02 = UNIT_L_FLOWER;
		unitType03 = UNIT_L_BEE;
	}
};

class ThreeBase : public GameBase {
public:
	ThreeBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::Three;
		unitType01 = UNIT_L_FLOWER;
		unitType02 = UNIT_D_FLY;
		unitType03 = UNIT_D_COAL;
	}
};

class FourBase : public GameBase {
public:
	FourBase(GameUnits *units) : GameBase::GameBase(units) {
		type = GameBaseTypes::Four;
		unitType01 = UNIT_D_FLY;
		unitType02 = UNIT_L_FLOWER;
		unitType03 = UNIT_D_COAL;
	}
};


class GameBasesContainer {
public:
	std::vector<GameBase*> bases;
	int currentBaseIndex;

	void switchBase(bool forward);
	void spawnUnit(int type);

	GameBase* getBaseAtLocation(Vector2D loc);
	GameBasesContainer(GameField &field, GameUnits &units);
	~GameBasesContainer();
};

