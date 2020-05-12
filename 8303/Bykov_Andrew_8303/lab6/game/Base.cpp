#include "Field.h"
#include "Unit_types.h"
#include "Base.h"
#include <sstream>
#include <vector>
#include "Adapter.h"

bool MoveCommand::execute(Base * base)
{
	return(base->setCommand(to_string(base->currentSquad) + " go " + direction));
}
bool AttackCommand::execute(Base * base)
{
	return(base->setCommand(to_string(base->currentSquad) + " attack " + x + " " + y));
}
bool CreateCommand::execute(Base * base)
{
	return(base->setCommand("Base create " + unit + " " + number));
}

void CompositeUnit::addUnit(Unit* p) {
	units.push_back(p);
	setLast(p);
}
void CompositeUnit::delUnit(Unit* p) {
	std::vector<Component*>::iterator iter = units.begin();
	while (iter != units.end()) {
		if (*iter = p) {
			units.erase(iter);
			return;
		}
	}
}
bool CompositeUnit::volunteer()
{
	return(Component::volunteer());
}


string Base::getCommand() const
{
	return command;
}
void Base::update()
{
	UnitsNumber = BerserksNumber = SpearmenNumber = 0;
	HuntersNumber = LongShootersNumber = UlansNumber = CuirassiersNumber = 0;
	spawnFree = true;

	std::vector<Component*>::iterator iter = army->units.begin();
	while (iter != army->units.end()) 
	{
		if ((*iter)->getCords() == spawnSpot && (*iter)->getSubclass() != "nan")
		{
			spawnFree = false;
		}
		if ((*iter)->getSubclass() == "Berserks")
		{
			UnitsNumber += (*iter)->getNumber();
			BerserksNumber += (*iter)->getNumber();
		}
		if ((*iter)->getSubclass() == "Spearmen")
		{
			UnitsNumber += (*iter)->getNumber();
			SpearmenNumber += (*iter)->getNumber();
		}
		if ((*iter)->getSubclass() == "Hunters")
		{
			UnitsNumber += (*iter)->getNumber();
			HuntersNumber += (*iter)->getNumber();
		}
		if ((*iter)->getSubclass() == "LongShooters")
		{
			UnitsNumber += (*iter)->getNumber();
			LongShootersNumber += (*iter)->getNumber();
		}
		if ((*iter)->getSubclass() == "Ulans")
		{
			UnitsNumber += (*iter)->getNumber();
			UlansNumber += (*iter)->getNumber();
		}
		if ((*iter)->getSubclass() == "Cuirassiers")
		{
			UnitsNumber += (*iter)->getNumber();
			CuirassiersNumber += (*iter)->getNumber();
		}
		iter++;
	}
}
void Base::update(Subject* subject) 
{
	removeUnit(static_cast<Unit *>(subject));
}
void Base::removeUnit(Unit *unit) 
{
	unit->delObs(this);
	army->delUnit(unit);
	SquadsNumber--;
}
void Base::printInfo()
{
	cout << "Base " + team + " INFO: \n";
	cout << "Gold = " << gold << endl;
	cout << "Health = " << health << endl;
	update();
	cout << "SquadsNumber = " << SquadsNumber << endl;
	cout << "UnitsNumber = " << UnitsNumber << endl;
	cout << "BerserksNumber = " << BerserksNumber << endl;
	cout << "SpearmenNumber = " << SpearmenNumber << endl;
	cout << "HuntersNumber = " << HuntersNumber << endl;
	cout << "LongShootersNumber = " << LongShootersNumber << endl;
	cout << "CuirassiersNumber = " << CuirassiersNumber << endl;
	cout << "UlansNumber = " << UlansNumber << endl << endl;
}
void Base::addGold(int money)
{
	gold += money;
	adapter->gold_Base(this);
}
bool Base::order(Command* command)
{
	return(command->execute(this));
}
bool Base::setCommand(string c)
{
	cout << currentSquad;
	command = c;
	istringstream iss(c);
	string token;
	getline(iss, token, ' ');
	if (token == "Base")
	{
		return(doCommand());
	}
	else
	{
		if (army->isEmpty())
		{
			adapter->noUnit();
			return false;
		}
		else
			return(army->volunteer());
	}
		
}
bool Base::doCommand()
{
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	getline(iss, token, ' ');
	if (token == "create")
	{
		getline(iss, token, ' ');
		if (token == "IB")
		{
			getline(iss, token, ' ');
			return(createBerserks(stoi(token)));
		}
		if (token == "IS")
		{
			getline(iss, token, ' ');
			return(createSpearmen(stoi(token)));
		}
		if (token == "AH")
		{
			getline(iss, token, ' ');
			return(createHunters(stoi(token)));
		}
		if (token == "AL")
		{
			getline(iss, token, ' ');
			return(createLongShooters(stoi(token)));
		}
		if (token == "CC")
		{
			getline(iss, token, ' ');
			return(createCuirassiers(stoi(token)));
		}
		if (token == "CU")
		{
			getline(iss, token, ' ');
			return(createUlans(stoi(token)));
		}

	}
	return false;
}
bool Base::place(Unit * U)
{
	update();
	if (spawnFree)
	{
		U->setBase(this);
		U->setField(field);
		U->setCords(spawnSpot);
		if(SquadsNumber == maxSpearmenNumber) return false;
		army->addUnit(U); SquadsNumber++;
		U->setSerialNumber(SquadsNumber);
		if (!field->addUnit(spawnSpot, U)) 
		{ 
			adapter->failCreateUnit_Base(this); 
			return false; 
		}
		U->addObs(this);
		U->setAdapter(adapter);
		update();
		lastUnit = U;
		adapter->createUnit_Base(this);
		return true;
		
	}
	adapter->failCreateUnit_Base(this);
	return false;
}
int  Base::getHealth() const
{
	return health;
}
int  Base::getGold() const
{
	return gold;
}
string Base::getTeam() const
{
	return team;
}
Point Base::getCords() const
{
	return baseSpot;
}
bool Base::destroyed()
{
	return(health <= 0);
}
bool Base::bankrupt()
{
	return(gold <= 0);
}

WaterBase::WaterBase(Point s, Point b, Field * f, Adapter * a) : Base(s, b, f, a)
{
	team = "Water";
	health = 999;
	gold = 500;

}
bool WaterBase::createBerserks(int N)
{
	if (N + BerserksNumber > maxBerserksNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	WaterBerserks * U = new WaterBerserks(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool WaterBase::createSpearmen(int N)
{
	if (N + SpearmenNumber > maxSpearmenNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	WaterSpearmen * U = new WaterSpearmen(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool WaterBase::createLongShooters(int N)
{
	if (N + LongShootersNumber > maxLongShootersNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	WaterLongShooters * U = new WaterLongShooters(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool WaterBase::createHunters(int N)
{
	if (N + HuntersNumber > maxHuntersNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	WaterHunters * U = new WaterHunters(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool WaterBase::createUlans(int N)
{
	if (N + UlansNumber > maxUlansNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	WaterUlans * U = new WaterUlans(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool WaterBase::createCuirassiers(int N)
{
	if (N + CuirassiersNumber > maxCuirassiersNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	WaterCuirassiers * U = new WaterCuirassiers(N, lastUnit);
	if (!place(U)) return false; 
	return true; 
}

FireBase::FireBase(Point s, Point b, Field * f, Adapter * a) : Base(s, b, f, a)
{
	team = "Fire";
	health = 999;
	gold = 500;
}
bool FireBase::createBerserks(int N)
{
	if (N + BerserksNumber > maxBerserksNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	FireBerserks * U = new FireBerserks(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool FireBase::createSpearmen(int N)
{
	if (N + SpearmenNumber > maxSpearmenNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	FireSpearmen * U = new FireSpearmen(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool FireBase::createLongShooters(int N)
{
	if (N + LongShootersNumber > maxLongShootersNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	FireLongShooters * U = new FireLongShooters(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool FireBase::createHunters(int N)
{
	if (N + HuntersNumber > maxHuntersNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	FireHunters * U = new FireHunters(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
bool FireBase::createUlans(int N)
{
	if (N + UlansNumber > maxUlansNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	FireUlans * U = new FireUlans(N, lastUnit);
	if (!place(U)) return false;
	return true;;
}
bool FireBase::createCuirassiers(int N)
{
	if (N + CuirassiersNumber > maxCuirassiersNumber || N + UnitsNumber > maxUnitsNumber)
	{
		adapter->overlimit_Base(this);
		return false;
	}
	FireCuirassiers * U = new FireCuirassiers(N, lastUnit);
	if (!place(U)) return false;
	return true;
}
