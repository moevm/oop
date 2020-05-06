#pragma once
#include "BoardUnit.h"
class Tree : public BoardUnit
{
public:
	std::vector<ActionMeta> turnAction() override;
	std::string getName() override;
	BoardUnit* getCopy() override;
};

