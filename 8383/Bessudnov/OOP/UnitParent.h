#pragma once
#include "GameUtilities.h"
#include "Interfaces.h"
#include <vector>

class UnitAtribute {
public:
	int parameterValueAbsolute;
	int parameterValueCurrent;

	void setPar(int value) {
		parameterValueAbsolute = value;
		parameterValueCurrent = value;
	}

	void increasePar(int increment) {
		parameterValueCurrent += increment;
	}


	UnitAtribute() : parameterValueAbsolute(0), parameterValueCurrent(0) {};
	UnitAtribute(int val) : parameterValueAbsolute(val), parameterValueCurrent(val) {};

	UnitAtribute &operator=(const UnitAtribute &atribute) {
		if (&atribute == this) return *this;

		this->parameterValueAbsolute = atribute.parameterValueAbsolute;
		this->parameterValueCurrent = atribute.parameterValueCurrent;

		return *this;

	}
};

typedef struct UnitProperties {
	bool isActive;
	char type;
	Vector2D location;
	UnitAtribute dew;
	UnitAtribute ligth;
	UnitAtribute moves;
	UnitAtribute damage;
	UnitAtribute sugar;

	UnitProperties() : isActive(false), type('1'), location(Vector2D(0, 0)), dew(), 
		ligth(), moves(), damage(), sugar() {	
	}

	UnitProperties &operator=(const UnitProperties &props) {
		if (this == &props) return *this;

		isActive = props.isActive;
		type = props.type;
		location = props.location;
		dew = props.dew;
		ligth = props.ligth;
		moves = props.moves;
		damage = props.damage;
		sugar = props.sugar;

		return *this;
	}
}UnitProperties;


class UnitParent : public IUnits, public IObserver {
public:
	UnitProperties unitProps;

	UnitParent();
	UnitParent(const UnitParent &unit);
	UnitParent &operator=(const UnitParent &unit);
	~UnitParent();

	void updateLocation(Vector2D newBorders);
	void move(Vector2D direction, Vector2D borders);
	virtual void attack() = 0;
	virtual void update() = 0;

protected:
	void setNewUnitLocation(Vector2D unitOffset, Vector2D borders);
};

class FlyingUnits : public UnitParent {
public:

};

class BeeUnit : public FlyingUnits {
public:
	BeeUnit() {
		unitProps.type = UNIT_L_BEE;
		unitProps.dew.setPar(3);
		unitProps.ligth.setPar(0);
		unitProps.moves.setPar(5);
		unitProps.damage.setPar(1);
		unitProps.sugar.setPar(2);
	}
	void attack();
	void update() {};
};

class FlyUnit : public FlyingUnits {
public:
	FlyUnit() {
		unitProps.type = UNIT_D_FLY;
		unitProps.dew.setPar(0);
		unitProps.ligth.setPar(3);
		unitProps.moves.setPar(4);
		unitProps.damage.setPar(2);
		unitProps.sugar.setPar(3);
	}
	void attack();
	void update() {};
};



class SmallUnits : public UnitParent {

};

class CollectorUnit : public SmallUnits {
public:
	CollectorUnit() {
		unitProps.type = UNIT_D_COLLECTOR;
		unitProps.dew.setPar(1);
		unitProps.ligth.setPar(0);
		unitProps.moves.setPar(1);
		unitProps.damage.setPar(1);
		unitProps.sugar.setPar(1);
	}
	void attack();
	void update() {};
};

class SprinklerUnit : public SmallUnits {
public:
	SprinklerUnit() {
		unitProps.type = UNIT_L_SPRINKLER;
		unitProps.dew.setPar(0);
		unitProps.ligth.setPar(1);
		unitProps.moves.setPar(1);
		unitProps.damage.setPar(1);
		unitProps.sugar.setPar(1);
	}
	void attack();
	void update() {};
};



class GroundUnits : public UnitParent {
	
};

class CoalUnit : public GroundUnits {
public:
	CoalUnit() {
		unitProps.type = UNIT_D_COAL;
		unitProps.dew.setPar(4);
		unitProps.ligth.setPar(0);
		unitProps.moves.setPar(3);
		unitProps.damage.setPar(3);
		unitProps.sugar.setPar(4);
	}
	void attack();
	void update() {};
};

class FlowerUnit : public GroundUnits {
public:

	FlowerUnit() {
		unitProps.type = UNIT_L_FLOWER;
		unitProps.dew.setPar(0);
		unitProps.ligth.setPar(5);
		unitProps.moves.setPar(4);
		unitProps.damage.setPar(2);
		unitProps.sugar.setPar(3);
	}
	void attack();
	void update() {};
};

class CompositeUnit : public UnitParent {
public:
	std::vector<UnitParent*> units;

	void addUnit(UnitParent* unit) {
		units.push_back(unit);
	}

	void setSize(size_t size) {
		units.resize(size);
	}

	~CompositeUnit() {
		units.clear();
	}

	void attack() {};

	void update() {
		for (auto &unit : units) {
			unit->update();
		}
	}
};

