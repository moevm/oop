#pragma once
# include <string>

class Unit;

class FieldObject
{
protected:
	std::string name;
	std::string shortName;
	bool canMove = false;
	bool alive = false;
public:
	virtual bool isMovable() = 0;
	virtual bool isAlive() = 0;

	virtual std::string getName() = 0;
	virtual std::string info() = 0;
	virtual FieldObject* copy() = 0;
	virtual std::string getShortName() = 0;
	virtual std::string getAbstractClass() = 0;
	virtual void unitInfluence(Unit* unit) = 0;



};