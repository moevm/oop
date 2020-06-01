#pragma once

class Unit;

class IBase {
public:
	virtual ~IBase() = default;
	virtual void onUnitDestroyed(Unit* destroyedUnit) = 0;
};

class IUnit {
protected:
	IBase* base;
public:
	virtual ~IUnit() = default;
	virtual void  attachBase(IBase* base) = 0;
};
