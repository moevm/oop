#pragma once
#include "AffectBehavior.h"
class LargeMedicineAffectBehavior :
	public AffectBehavior
{
public:
	LargeMedicineAffectBehavior();
	~LargeMedicineAffectBehavior();
	void affectOnUnit(std::shared_ptr<Unit> unit);
};

