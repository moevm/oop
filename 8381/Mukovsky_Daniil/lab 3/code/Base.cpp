#include "Base.h"

Base::Base(int maxCreateUnits, PlayingField* field, int X, int Y,bool team) {
	this->maxCreateUnits = maxCreateUnits;
	this->field = field;
	healPoints = 40;
	this->team = team;
	warriorFactory = new WarriorFactory();
	shooterFactory = new ShooterFactory();
	bufferFactory = new BufferFactory();
	flyweightFactory = new FlyweightFactory({ {"green"},{"white"},{"red"},{"blue"} });  //заранее инициализируем некоторые цвета

	name = "Base";
	shortName = "_B_";
	canMove = false;
	alive = true;

	if (!field->addObject(this, X, Y)) {
		std::cout << "Base: Base don't added to the field\n";
		alive = false;
		return;
	}

	std::cout << "Base: Base added to the field\n";
}

std::string Base::getShortName() {
	return shortName;
}

std::string Base::getName() {
	return name;
}

std::string Base::info() {
	std::string player;
	team ? player = "1" : player = "2";
	std::string out = "Class: Base player: "+player+", current healpoints: " + std::to_string(healPoints) +  ",	cur created units: "+ std::to_string(units.size())+",	max created units: "+std::to_string(maxCreateUnits);
	return out;
}

void Base::setMaxCreateUnits(int newMax) {
	maxCreateUnits = newMax;
}

bool Base::createUnit(std::string UnitType, std::string color,unsigned row, unsigned column)
{
	if (!field->checkCoordinate(row,column)) {
		return false;
	}

	if (maxCreateUnits == units.size()) {
		std::cout << "Base: Base can't create more units\n";
		return false;
	}

	Unit* newUnit;
	Flyweight newFlyweight = flyweightFactory->GetFlyweight({color}); //если легковес с таким цветом существует возвращает его, иначе возвращает новый легковес
	if (UnitType == "W_t") {
		newUnit = warriorFactory->createTank();
	}
	else if (UnitType == "W_d") {
		newUnit = warriorFactory->createDamager();
	}
	else if (UnitType == "S_t") {
		newUnit = shooterFactory->createTank();
	}
	else if (UnitType == "S_d") {
		newUnit = shooterFactory->createDamager();
	}
	else if (UnitType == "B_t") {
		newUnit = bufferFactory->createTank();
	}
	else if (UnitType == "B_d") {
		newUnit = bufferFactory->createDamager();
	}
	else {
		std::cout << "Base: Wrong UnitType \n";
		return false;
	}
	
	newUnit->setFlyweight(&newFlyweight);
	newUnit->attachBase(this);
	newUnit->setTeam(team);
	units.push_back(newUnit);

	if (field->addUnit(newUnit, row, column)) {
		std::cout << "Base: Unit added correctly\n";
	}
	else {
		std::cout << "Base: Unit was not added to the field\n";
		delete newUnit;
		return false;
	}

	return true;
}



Unit* Base::createUnit_(std::string UnitType, std::string color,  unsigned row, unsigned column)
{
	if (!field->checkCoordinate(row, column)) {
		return nullptr;
	}

	if (maxCreateUnits == units.size()) {
		std::cout << "Base: Base can't create more units\n";
		return nullptr;
	}

	Unit* newUnit;
	Flyweight newFlyweight = flyweightFactory->GetFlyweight({ color }); //если легковес с таким цветом существует возвращает его, иначе возвращает новый легковес
	if (UnitType == "W_t") {
		newUnit = warriorFactory->createTank();
	}
	else if (UnitType == "W_d") {
		newUnit = warriorFactory->createDamager();
	}
	else if (UnitType == "S_t") {
		newUnit = shooterFactory->createTank();
	}
	else if (UnitType == "S_d") {
		newUnit = shooterFactory->createDamager();
	}
	else if (UnitType == "B_t") {
		newUnit = bufferFactory->createTank();
	}
	else if (UnitType == "B_d") {
		newUnit = bufferFactory->createDamager();
	}
	else {
		std::cout << "Base: Wrong UnitType \n";
		return nullptr;
	}

	newUnit->setFlyweight(&newFlyweight);
	newUnit->attachBase(this);
	newUnit->setTeam(team);
	units.push_back(newUnit);

	if (field->addUnit(newUnit, row, column)) {
		std::cout << "Base: Unit added correctly\n";
	}
	else {
		std::cout << "Base: Unit was not added to the field\n";
		delete newUnit;
		return nullptr;
	}

	return newUnit;
}



