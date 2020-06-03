#pragma once
#include "NeutralBoardUnit.h"
class TreeLog : public NeutralBoardUnit
{
public:
	std::vector<ActionMeta> turnAction() override;
	std::string getName() override;
};

