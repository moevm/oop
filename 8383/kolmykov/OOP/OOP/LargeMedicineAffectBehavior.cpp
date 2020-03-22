#include "LargeMedicineAffectBehavior.h"



LargeMedicineAffectBehavior::LargeMedicineAffectBehavior()
{
}


LargeMedicineAffectBehavior::~LargeMedicineAffectBehavior()
{
}

void LargeMedicineAffectBehavior::affectOnUnit(std::shared_ptr<Unit> unit)
{
	unit->addHP(100);
}
