#include "SmallArmorObject.h"



SmallArmorObject::SmallArmorObject()
{
	affectBehavior = std::shared_ptr<AffectBehavior>(new SmallArmorAffectBehavior());
	type = ObjectType::SMALL_ARMOR;
}


SmallArmorObject::~SmallArmorObject()
{
}

//void SmallArmorObject::operator+=(Unit& unit)
//{
//	affectOnUnit(std::shared_ptr<Unit>(&unit));
//}
