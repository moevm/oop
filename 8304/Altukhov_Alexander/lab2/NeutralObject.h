#pragma once
#include "INeutralObject.h"
#include "Strategy.h"
#include "TowerStrategy.h"
#include "ShrineStrategy.h"
#include "GunStrategy.h"
#include "WeaponryStrategy.h"
enum class NeutralObjectTypes {
	TOWER, WEAPONRY, GUN, SHRINE
};

class NeutralObject :public INeutralObject {

	NeutralObjectTypes type;
	Strategy* strategy;

public:

	NeutralObject() = default;
	~NeutralObject() = default;
	NeutralObjectTypes getNeutralObjectType();
	void setNeutralObjectType(NeutralObjectTypes type);
	void applyEffect(Unit*& unit);
	void removeEffect(Unit*& unit);
	void selectStrategy();
};

