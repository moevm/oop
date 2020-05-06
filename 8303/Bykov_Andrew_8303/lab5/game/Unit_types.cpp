#include "Field.h"
#include "Base.h"
#include "Unit_types.h"
#include <sstream>


EmptyUnit::EmptyUnit() : Unit()
{
	setNumber(0);
	army = "nan";
	s_class = "nan";
}

Infantry :: Infantry(Component *n ) : Unit(n)
{
	army = "Infantry";
}
Berserks::Berserks(int N, Component *n ) : Infantry(n)
{
	setNumber(N);
	s_class = "Berserks";
}
Spearmen::Spearmen(int N, Component *n ) : Infantry(n)
{
	setNumber(N);
	s_class = "Spearmen";
}

Archers :: Archers(Component *n) : Unit(n)
{
	army = "Archers";
}
Hunters::Hunters(int N, Component *n ) : Archers(n)
{
	setNumber(N);
	s_class = "Hunters";
}
LongShooters::LongShooters(int N, Component *n) : Archers(n)
{
	setNumber(N);
	s_class = "LongShooters";
}

Cavalry :: Cavalry(Component *n) : Unit(n)
{
	army = "Cavalry";
}
Cuirassiers::Cuirassiers(int N, Component *n) : Cavalry(n)
{
	setNumber(N);
	s_class = "Cuirassiers";
}
Ulans::Ulans(int N, Component *n) : Cavalry(n)
{
	setNumber(N);
	s_class = "Ulans";
}
/*
bool Berserks::update()
{
	string command = base->getCommand();
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
	string command = base->getCommand();
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
	string command = base->getCommand();
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
	string command = base->getCommand();
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
	string command = base->getCommand();
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
	string command = base->getCommand();
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
*/
bool Berserks::volunteer()
{
	string command = base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "I" || token == "IB" || token == to_string(properties.serialNumber)))
	{
		Component::volunteer();
		return false;
	}
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
		AttackMediator(this, field->getUnit(x, y));
		return(interact());
	}
	cout << "fail command\n";
	return false;
}
bool Spearmen::volunteer()
{
	string command = base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "I" || token == "IS" || token == to_string(properties.serialNumber)))
	{
		Component::volunteer();
		return false;
	}
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
		AttackMediator(this, field->getUnit(x, y));
		return(interact());
	}
	cout << "fail command\n";
	return false;

}
bool Hunters::volunteer()
{
	string command = base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "A" || token == "AH" || token == to_string(properties.serialNumber)))
	{
		Component::volunteer();
		return false;
	}
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
		AttackMediator(this, field->getUnit(x, y));
		return(interact());
	}
	cout << "fail command\n";
	return false;
}
bool LongShooters::volunteer()
{
	string command = base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "A" || token == "AL" || token == to_string(properties.serialNumber)))
	{
		Component::volunteer();  
		return false; 
	}
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
		AttackMediator(this, field->getUnit(x, y));
		return(interact());
	}
	cout << "fail command\n";
	return false;
}
bool Ulans::volunteer()
{
	string command = base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "C" || token == "CU" || token == to_string(properties.serialNumber)))
	{
		Component::volunteer();
		return false;
	}
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
		AttackMediator(this, field->getUnit(x, y));
		return(interact());
	}
	cout << "fail command\n";
	return false;
}
bool Cuirassiers::volunteer()
{
	string command = base->getCommand();
	istringstream iss(command);
	string token;
	getline(iss, token, ' ');
	if (!(token == "All" || token == "C" || token == "CC" || token == to_string(properties.serialNumber)))
	{
		Component::volunteer();
		return false;
	}
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
		AttackMediator(this, field->getUnit(x, y));
		return(interact());
	}
	cout << "fail command\n";
	return false;
}

