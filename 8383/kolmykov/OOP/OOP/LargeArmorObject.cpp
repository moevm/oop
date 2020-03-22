#include "LargeArmorObject.h"



LargeArmorObject::LargeArmorObject()
{
	affectBehavior = std::shared_ptr<AffectBehavior>(new LargeArmorAffectBehavior());
	type = ObjectType::LARGE_ARMOR_OBJECT;
}


LargeArmorObject::~LargeArmorObject()
{
}
