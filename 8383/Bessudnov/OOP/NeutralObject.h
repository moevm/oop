#pragma once
#include "Interfaces.h"
#include "GameUtilities.h"
#include "UnitParent.h"
#include <string>
#include <vector>

class Vector2D;

enum NeutralObjects {Apple = 6, Dew, Ligth, Branch};

class NeutralObject : public INeutralObjects{
public:
	Vector2D location;
	NeutralObjects type;
	NeutralObject();
	~NeutralObject();

	virtual void onExecute(GameUnits &units) = 0;
};

class AppleObject : public NeutralObject {
public:
	AppleObject() {
		type = NeutralObjects::Apple;
	}
	
	void onExecute(GameUnits &units);
};

class DewObject : public NeutralObject {
public:
	DewObject() {
		type = NeutralObjects::Dew;
	}

	void onExecute(GameUnits &units);
};

class LigthObject : public NeutralObject {
public:
	LigthObject() {
		type = NeutralObjects::Ligth;
	}

	void onExecute(GameUnits &units);
};

class BranchObject : public NeutralObject {
public:
	BranchObject() {
		type = NeutralObjects::Branch;
	}

	void onExecute(GameUnits &units);
};


class NeutralObjectContainer {
private:
	NeutralObject *object;
	std::vector<NeutralObject*> objects;
public:
	NeutralObjectContainer(std::string fileName);
	NeutralObject* getObjectAtLocation(Vector2D loc);
	void useObject(GameUnits &units);
	~NeutralObjectContainer();

	bool operator==(const GameUnits &units);
};

