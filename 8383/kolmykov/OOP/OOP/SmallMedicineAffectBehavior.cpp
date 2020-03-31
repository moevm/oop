#include "SmallMedicineAffectBehavior.h"



SmallMedicineAffectBehavior::SmallMedicineAffectBehavior()
{
}


SmallMedicineAffectBehavior::~SmallMedicineAffectBehavior()
{
}

void SmallMedicineAffectBehavior::affectOnUnit(std::shared_ptr<Unit> unit)
{
	unit->addHP(50);
}
