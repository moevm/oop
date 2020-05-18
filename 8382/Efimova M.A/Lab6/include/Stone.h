#pragma once
#include "NeutralBoardUnit.h"
class Stone : public NeutralBoardUnit
{
public:
	std::vector<ActionMeta> turnAction() override;
	std::string getName() override;
};

