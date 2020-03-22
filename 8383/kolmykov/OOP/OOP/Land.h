#pragma once
#include "LandInterface.h"
#include "LandType.h"


class Land : LandInterface
{
protected:
	LandType type;
public:
	
	Land();
	~Land();
	virtual void bufUnit(std::shared_ptr<Unit> unit);
	virtual char getChar();
	LandType getType();
};

