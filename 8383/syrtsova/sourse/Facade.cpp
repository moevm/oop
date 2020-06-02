#include "pch.h"
#include "Facade.h"

bool Facade::generation() {
	land = new Landscape(_x_max, _y_max, field);
	neutral = new Creating(_x_max, _y_max, field);
	std::cout << std::endl;
	base->getBase();
	return true;
}