#pragma once
#include "Strategy.h"
class GunStrategy : public Strategy {

public:
	virtual void applyEffect(Unit*& target);
	virtual void removeEffect(Unit*& target);
};

