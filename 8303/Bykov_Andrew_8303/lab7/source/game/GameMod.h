#pragma once
#include "GameRules.h"
#include "Adapter.h"
#include "Base.h"
#include "Field.h"

template <typename T>
class GameBase {
public:
	Field* field = nullptr;
	Base * base[2];
	Adapter* adapter;
	int finish;
};

template <typename RuleBase>
class Game : public GameBase<RuleBase> {

};

template<>
class Game<Rule1> : public GameBase<Rule1> 
{
	Adapter* adapter;
	Rule1* rule;
	static Game<Rule1> *game;
public:

	static Game<Rule1>* getInstance()
	{
		if (game == nullptr)
			game = new Game<Rule1>;
		return game;
	}

	void startGame();

	bool doCommand(Command * com) 
	{
		rule->doCommand(com, base);
		finish = rule->lose(field);
		if (finish) 
		{
			if (finish == 1) 
			{
				adapter->lose(1);
				return false;
			}
			else if (finish == 2) 
			{
				adapter->lose(2);
				return false;
			}
		}
		return true;
	}
};

template<>
class Game<Rule2> : public GameBase<Rule2>
{
	Adapter* adapter;
	Rule2* rule;
	static Game<Rule2> *game;
public:

	static Game<Rule2>* getInstance() 
	{
		if (game == nullptr)
			game = new Game<Rule2>;
		return game;
	}

	void startGame();


	bool doCommand(Command * com) 
	{
		rule->doCommand(com, base);
		finish = rule->lose(field);
		if (finish)
		{
			if (finish == 1)
			{
				adapter->lose(1);
				return false;
			}
			else if (finish == 2)
			{
				adapter->lose(2);
				return false;
			}
		}
		return true;
	}

};
