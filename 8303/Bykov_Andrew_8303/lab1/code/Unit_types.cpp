#include "Unit_types.h"
#include "Field.h"
#include <sstream>
EmptyUnit::EmptyUnit() : Unit()
{
	setNumber(0);
	army = "  ";
	s_class = "  ";
}

Infantry :: Infantry() : Unit()
{
	army = "Infantry";
}
Berserks::Berserks(int N) : Infantry()
{
	setNumber(N);
	s_class = "Berserks";
}
Spearmen::Spearmen(int N) : Infantry()
{
	setNumber(N);
	s_class = "Spearmen";
}

Archers :: Archers() : Unit()
{
	army = "Archers";
}
Hunters::Hunters(int N) : Archers()
{
	setNumber(N);
	s_class = "Hunters";
}
LongShooters::LongShooters(int N) : Archers()
{
	setNumber(N);
	s_class = "LongShooters";
}

Cavalry :: Cavalry() : Unit()
{
	army = "Cavalry";
}
Cuirassiers::Cuirassiers(int N) : Cavalry()
{
	setNumber(N);
	s_class = "Cuirassiers";
}
Ulans::Ulans(int N) : Cavalry()
{
	setNumber(N);
	s_class = "Ulans";
}

bool Berserks::update()
{
	string command = properties.base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' '); 
	if (!(token == "All" || token == "I" || token == "IB" || token == to_string(properties.serialNumber)))
		return false;
	getline(iss, token, ' ');
	if (token == "go")
	{
		getline(iss, token, ' ');
		return(go(token));
	}
	if (token == "attack")
	{
		getline(iss, token, ' ');
		int x = stoi(token);
		getline(iss, token, ' ');
		int y = stoi(token);
		return(attack(x, y));
	}
	cout << "fail command\n";
	return false;
}
bool Spearmen::update()
{
	string command = properties.base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "I" || token == "IS" || token == to_string(properties.serialNumber)))
		return false;
	getline(iss, token, ' ');
	if (token == "go")
	{
		getline(iss, token, ' ');
		return(go(token));
	}
	if (token == "attack")
	{
		getline(iss, token, ' ');
		int x = stoi(token);
		getline(iss, token, ' ');
		int y = stoi(token);
		return(attack(x, y));
	}
	cout << "fail command\n";
	return false;

}
bool Hunters::update()
{
	string command = properties.base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "A" || token == "AH" || token == to_string(properties.serialNumber)))
		return false;
	getline(iss, token, ' ');
	if (token == "go")
	{
		getline(iss, token, ' ');
		return(go(token));
	}
	if (token == "attack")
	{
		getline(iss, token, ' ');
		int x = stoi(token);
		getline(iss, token, ' ');
		int y = stoi(token);
		return(attack(x, y));
	}
	cout << "fail command\n";
	return false;
}
bool LongShooters::update()
{
	string command = properties.base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "A" || token == "AL" || token == to_string(properties.serialNumber)))
		return false;
	getline(iss, token, ' ');
	if (token == "go")
	{
		getline(iss, token, ' ');
		return(go(token));
	}
	if (token == "attack")
	{
		getline(iss, token, ' ');
		int x = stoi(token);
		getline(iss, token, ' ');
		int y = stoi(token);
		return(attack(x, y));
	}
	cout << "fail command\n";
	return false;
}
bool Ulans::update()
{
	string command = properties.base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "C" || token == "CU" || token == to_string(properties.serialNumber)))
		return false;
	getline(iss, token, ' ');
	if (token == "go")
	{
		getline(iss, token, ' ');
		return(go(token));
	}
	if (token == "attack")
	{
		getline(iss, token, ' ');
		int x = stoi(token);
		getline(iss, token, ' ');
		int y = stoi(token);
		return(attack(x, y));
	}
	cout << "fail command\n";
	return false;
}
bool Cuirassiers::update()
{
	string command = properties.base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "C" || token == "CC" || token == to_string(properties.serialNumber)))
		return false;
	getline(iss, token, ' ');
	if (token == "go")
	{
		getline(iss, token, ' ');
		return(go(token));
	}
	if (token == "attack")
	{
		getline(iss, token, ' ');
		int x = stoi(token);
		getline(iss, token, ' ');
		int y = stoi(token);
		return(attack(x, y));
	}
	cout << "fail command\n";
	return false;
}

CompositeUnit :: CompositeUnit()
{
	units = new Unit*[maxSquadsNumber];
}
void CompositeUnit::addUnit(Unit* p) {
	if (num == maxSquadsNumber - 1) { cout << "over limit\n"; return; }
	p->setSerialNumber(num);
	units[num++] = p;
}
void CompositeUnit::delUnit(Unit* p) {
	for (int i = 0; i < num; i++)
		if (p == units[i])
		{
			for (i; i < num - 1; i++)
				units[i] = units[i + 1];
			units[--num] = nullptr;
			return;
		}
}
bool CompositeUnit::notify()
{
	bool f = false;
	for (int i = 0; i < num; i++)
		if(units[i]->update()) f = true;
	return f;
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
	for (int i = 0; i < army->num; i++)
	{
		if (army->units[i]->getCords() == spawnSpot)
		{
			spawnFree = false;
		}
		if (army->units[i]->getSubclass() == "Berserks")
		{
			UnitsNumber += army->units[i]->getNumber();
			BerserksNumber += army->units[i]->getNumber();
		}
		if (army->units[i]->getSubclass() == "Spearmen")
		{
			UnitsNumber += army->units[i]->getNumber();
			SpearmenNumber += army->units[i]->getNumber();
		}
		if (army->units[i]->getSubclass() == "Hunters")
		{
			UnitsNumber += army->units[i]->getNumber();
			HuntersNumber += army->units[i]->getNumber();
		}
		if (army->units[i]->getSubclass() == "LongShooters")
		{
			UnitsNumber += army->units[i]->getNumber();
			LongShootersNumber += army->units[i]->getNumber();
		}
		if (army->units[i]->getSubclass() == "Ulans")
		{
			UnitsNumber += army->units[i]->getNumber();
			UlansNumber += army->units[i]->getNumber();
		}
		if (army->units[i]->getSubclass() == "Cuirassiers")
		{
			UnitsNumber += army->units[i]->getNumber();
			CuirassiersNumber += army->units[i]->getNumber();
		}
	}
}
bool Base::setCommand(string c)
{
	command = c;
	istringstream iss(c);
	string token;
	getline(iss, token, ' ');
	if (token == "Base")
	{
		return(doCommand());
	}
	else
		return(army->notify());
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
	cout << "Base: unknown command\n";
	return false;
}
void Base::printInfo()
{
	update();
	cout << "N = "  << UnitsNumber << endl;
	cout << "IB = " << BerserksNumber << endl;
	cout << "IS = " << SpearmenNumber << endl;
	cout << "AH = " << HuntersNumber << endl;
	cout << "AL = " << LongShootersNumber << endl;
	cout << "CC = " << CuirassiersNumber << endl;
	cout << "CU = " << UlansNumber << endl;
}
bool Base::place(Unit * U)
{
	update();
	if (spawnFree)
	{
		U->setBase(this);
		U->setField(field);
		U->setCords(spawnSpot);
		if (!field->addUnit(spawnSpot, U)) return false;
		army->addUnit(U);
		update();
		return true;
	}
	cout << "Base: Can't create, spawn is'n free\n";
	return false;
}

WaterBase :: WaterBase(Point s, Point b, Field * f) : Base(s, b, f)
{
	health = 1000;
	createBerserks(10);
	//createSpearmen(5);
	//createHunters(2);
	//createLongShooters(2);
	//createUlans(3);
	//createCuirassiers(1);
}
bool WaterBase::createBerserks(int N)
{
	if (N + BerserksNumber > maxBerserksNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	WaterBerserks * U = new WaterBerserks(N);
	if(!place(U)) return false;
	return true;
}
bool WaterBase::createSpearmen(int N)
{
	if (N + SpearmenNumber > maxSpearmenNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	WaterSpearmen * U = new WaterSpearmen(N);
	if(!place(U)) return false;
	return true;
}
bool WaterBase::createLongShooters(int N)
{
	if (N + LongShootersNumber > maxLongShootersNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	WaterLongShooters * U = new WaterLongShooters(N);
	if(!place(U)) return false;
	return true;
}
bool WaterBase::createHunters(int N)
{
	if (N + HuntersNumber > maxHuntersNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	WaterHunters * U = new WaterHunters(N);
	if(!place(U)) return false;
	return true;
}
bool WaterBase::createUlans(int N)
{
	if (N + UlansNumber > maxUlansNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	WaterUlans * U = new WaterUlans(N);
	if(!place(U)) return false;
	return true;
}
bool WaterBase::createCuirassiers(int N)
{
	if (N + CuirassiersNumber > maxCuirassiersNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	WaterCuirassiers * U = new WaterCuirassiers(N);
	if(!place(U)) return false;
	return true;
}

FireBase::FireBase(Point s, Point b, Field * f) : Base(s, b, f)
{
	health = 1000;
	createBerserks(10);
	//createSpearmen(5);
	//createHunters(2);
	//createLongShooters(2);
	//createUlans(3);
	//createCuirassiers(1);
}
bool FireBase::createBerserks(int N)
{
	if (N + BerserksNumber > maxBerserksNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	FireBerserks * U = new FireBerserks(N);
	if(!place(U)) return false;
	return true;
}
bool FireBase::createSpearmen(int N)
{
	if (N + SpearmenNumber > maxSpearmenNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	FireSpearmen * U = new FireSpearmen(N);
	if(!place(U)) return false;
	return true;
}
bool FireBase::createLongShooters(int N)
{
	if (N + LongShootersNumber > maxLongShootersNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	FireLongShooters * U = new FireLongShooters(N);
	if(!place(U)) return false;
	return true;
}
bool FireBase::createHunters(int N)
{
	if (N + HuntersNumber > maxHuntersNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	FireHunters * U = new FireHunters(N);
	if(!place(U)) return false;
	return true;
}
bool FireBase::createUlans(int N)
{
	if (N + UlansNumber > maxUlansNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	FireUlans * U = new FireUlans(N);
	if(!place(U)) return false;
	return true;;
}
bool FireBase::createCuirassiers(int N)
{
	if (N + CuirassiersNumber > maxCuirassiersNumber || N + UnitsNumber > maxUnitsNumber)
		return false;
	FireCuirassiers * U = new FireCuirassiers(N);
	if(!place(U)) return false;
	return true;
}

