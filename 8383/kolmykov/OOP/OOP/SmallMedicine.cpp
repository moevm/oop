#include "SmallMedicine.h"



SmallMedicine::SmallMedicine()
{
	affectBehavior = std::shared_ptr<AffectBehavior>(new SmallMedicineAffectBehavior());
	type = ObjectType::SMALL_MEDICINE;
}


SmallMedicine::~SmallMedicine()
{
}
