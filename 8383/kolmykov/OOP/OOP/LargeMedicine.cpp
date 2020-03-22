#include "LargeMedicine.h"



LargeMedicine::LargeMedicine()
{
	affectBehavior = std::shared_ptr<AffectBehavior>(new LargeMedicineAffectBehavior());
	type = ObjectType::LARGE_MEDICINE;
}


LargeMedicine::~LargeMedicine()
{
}
