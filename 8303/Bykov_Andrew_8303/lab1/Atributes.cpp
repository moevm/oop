#include "Atributes.h"

void Physical::kill()
{
	health = 0;
}

void Physical::heal()
{
	health = max_health;
}

void Physical::setMaxHealth(int H)
{
	max_health = health = H;
}

