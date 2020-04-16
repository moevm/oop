#include "StinkingBody.h"



StinkingBody::StinkingBody() {
	range = 1;
	damage = 80;
}

StinkingBody::StinkingBody(const StinkingBody & other):Weapon(other)
{
}


StinkingBody::~StinkingBody()
{
}
