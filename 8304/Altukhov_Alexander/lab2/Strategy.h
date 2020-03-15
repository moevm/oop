#pragma once
#include "Unit.h"

class Strategy
{
public:
	virtual void applyEffect(Unit*& target) = 0;
	virtual void removeEffect(Unit*& target) = 0;
};

