#pragma once
#include "AffectBehavior.h"
class SmallMedicineAffectBehavior :
	public AffectBehavior
{
public:
	SmallMedicineAffectBehavior();
	~SmallMedicineAffectBehavior();
	void affectOnUnit(std::shared_ptr<Unit> unit);
};

