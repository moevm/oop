#pragma once
#include "Unit.h"

class Landscape : public FieldObject
{
public:
	virtual ~Landscape() = default;
	virtual bool canHoldFieldObject(FieldObject* object = nullptr) const = 0;
	virtual void checkUnitRange(FieldObject* object) const = 0;
	virtual Landscape* copy() = 0;
	virtual std::string info() = 0;
	bool isAlive() {
		return false;
	}
	bool isMovable() {
		return canMove;
	}
	virtual std::string getName() {
		return name;
	}
	virtual std::string getShortName() {
		return shortName;
	}
	virtual void unitInfluence(Unit* unit) {}

	virtual std::string getAbstractClass() {
		return "Landscape";
	}
	bool getTeam() { return false; };
	void setAlive(bool flag) {};
	void getDamage(int a) {};
};


class LandscapeProxy : public Landscape
{
private:
	Landscape* landscape;
public:
	LandscapeProxy(Landscape* landscape)
	{
		this->landscape = landscape;
		canMove = false;
	}
	virtual std::string getName() {
		return landscape->getName();
	}
	virtual std::string getShortName() {
		return landscape->getShortName();
	}
	virtual std::string info() {
		return landscape->info();
	}
	bool canHoldFieldObject(FieldObject* unit = nullptr) const
	{
		return landscape->canHoldFieldObject(unit);
	}
	void checkUnitRange(FieldObject* unit) const
	{
		return landscape->checkUnitRange(unit);
	}
	Landscape* copy()
	{
		return new LandscapeProxy(landscape);
	}
};

class Mountains : public Landscape
{
public:
	Mountains();
	bool canHoldFieldObject(FieldObject* unit = nullptr) const;
	void checkUnitRange(FieldObject* unit) const;
	Landscape* copy();
	virtual std::string info();
};


class Ground : public Landscape
{
public:
	Ground();
	bool canHoldFieldObject(FieldObject* unit = nullptr) const;
	void checkUnitRange(FieldObject* unit) const;
	Landscape* copy();
	virtual std::string info();
};


class Water : public Landscape
{
public:
	Water();
	bool canHoldFieldObject(FieldObject* unit = nullptr) const;
	void checkUnitRange(FieldObject* unit) const;
	Landscape* copy();
	virtual std::string info();
};

