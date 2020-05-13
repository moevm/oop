#include "GameMod.h"
#include "Exeptions.h"

void Game<Rule1> :: startGame()
{
	adapter = new Adapter();
	rule = new Rule1();
	if (field) delete field;
	try
	{
		field = rule->startField(adapter);
	}
	catch (LogicException exept)
	{
		std::cout << exept.what() << std::endl;
		std::cout << "Incorrect data, GameRules file was damaged." << std::endl;
		system("pause");
		exit(1);
	}
	base[0] = field->getWater();
	base[1] = field->getFire();
}

void  Game<Rule2> :: startGame()
{
	adapter = new Adapter();
	rule = new Rule2();
	if (field) delete field;
	try
	{
		field = rule->startField(adapter);
	}
	catch (LogicException exept)
	{
		std::cout << exept.what() << std::endl;
		std::cout << "Incorrect data, GameRules file was damaged." << std::endl;
		system("pause"); 
		exit(1);
	}
	base[0] = field->getWater();
	base[1] = field->getFire();
}