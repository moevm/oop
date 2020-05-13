#include "GameRules.h"
#include "Field.h"
#include "Base.h"
#include "Adapter.h"
bool Status1::doCommand(Command * com, Base ** base) {
	return(base[0]->order(com));
}
bool Status2::doCommand(Command * com, Base ** base) {
	return(base[1]->order(com));
}

RuleBase::RuleBase() {
	status1 = new Status1();
	status2 = new Status2();
	currentStatus = status1;
}
void RuleBase :: changeStatus() 
{
	if (currentStatus == status1) {
		currentStatus = status2;
		adapter->step(2);
	}
	else {
		currentStatus = status1;
		adapter->step(1);
	}
}

Field* Rule1 :: startField(Adapter* Adapter) 
{
	adapter = Adapter;
	field = new Field(20, 10, adapter);
	field->addNetral(Point(2, 9), new Trap());
	field->addNetral(Point(3, 9), new Rune());
	field->addNetral(Point(4, 9), new Curse());
	field->addNetral(Point(5, 9), new Gold());

	field->addLand(Point(6, 12), new SwampProxy());
	field->addLand(Point(7, 12), new SwampProxy());
	field->addLand(Point(6, 13), new SwampProxy());
	field->addLand(Point(7, 13), new SwampProxy());

	field->addLand(Point(2, 12), new RiverProxy());
	field->addLand(Point(3, 12), new RiverProxy());
	field->addLand(Point(2, 13), new RiverProxy());
	field->addLand(Point(3, 13), new RiverProxy());

	field->addLand(Point(2, 16), new ForestProxy());
	field->addLand(Point(3, 16), new ForestProxy());
	field->addLand(Point(2, 17), new ForestProxy());
	field->addLand(Point(3, 17), new ForestProxy());
	return field;
}
int Rule1::lose(Field* field) 
{
	if (field->getWater()->destroyed())
		return 1;
	else if (field->getFire()->destroyed())
		return 2;
	else
		return 0;
}
void Rule1::doCommand(Command * com, Base ** base)
{
	if (currentStatus->doCommand(com, base))
		changeStatus();
}

Field* Rule2::startField(Adapter* Adapter) 
{
	adapter = Adapter;
	field = new Field(20, 10, adapter);
	field->addNetral(Point(5, 9), new Gold());
	field->addNetral(Point(10, 9), new Gold());
	field->addNetral(Point(6, 6), new Gold());
	field->addNetral(Point(7, 7), new Gold());

	return field;
}
int Rule2::lose(Field* field) 
{
	if (field->getWater()->bankrupt() || field->getWater()->destroyed())
		return 1;
	else if (field->getFire()->bankrupt() || field->getFire()->destroyed())
		return 2;
	else
	{
		field->getWater()->setGold(field->getWater()->getGold() - 20);
		field->getFire()->setGold(field->getFire()->getGold() - 20);
		return 0;
	}
		
}
void Rule2::doCommand(Command * com, Base ** base)
{
	if (currentStatus->doCommand(com, base))
		changeStatus();
}