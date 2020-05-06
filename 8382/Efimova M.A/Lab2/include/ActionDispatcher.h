#pragma once
#include "Board.h"
#include <queue>
class ActionDispatcher
{
public:
	ActionDispatcher(Board* board);
	void push_back(BoardUnit::ActionMeta meta);
	void flush();
	void exec(BoardUnit::ActionMeta meta);
protected:

	Board* mBoard = nullptr;
};

