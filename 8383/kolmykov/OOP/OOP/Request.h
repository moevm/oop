#pragma once
#include "UnitFactory.h"
#include "Kind.h"


struct Request {
	int coordX1;
	int coordY1;
	int coordX2;
	int coordY2;
	std::shared_ptr<UnitFactory> factory;
	Kind kind;
};

