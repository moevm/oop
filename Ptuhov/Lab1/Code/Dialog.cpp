#include "Dialog.h"

void Dialog::start()
{
	std::cout << greeting;
	speak();
}

void Dialog::speak()
{
	while (true)
	{
		std::cout << chooseOption;
		for (auto& opt : options)
			std::cout << opt;
		std::cout << choiseRequest;
		int choise = 5;
		std::cin >> choise;
		switch (choise)
		{
		case 1:
		{
			createFieldChoise();
			break;
		}
		case 2:
		{
			addUnitChoise();
			break;
		}
		case 3:
			removeUnitChoise();
			break;
		case 4:
			std::cout << fld;
			break;
		case 5:
			return;
		default:
			std::cout << "Try again\n\n";
			break;
		}
	}
}

void Dialog::createFieldChoise()
{
	int width = 0;
	int length = 0;
	std::cout << "Set width and length: ";
	std::cin >> width;
	std::cin >> length;

	if (width <= 0 || length <= 0)
	{
		std::cout << "Incorrect args. Try again\n\n";
		createFieldChoise();
		return;
	}

	Field new_fld(width, length);
	fld = new_fld;

	std::cout << "\nField created\n";
}

void Dialog::addUnitChoise()
{
	Point p;
	std::cout << "Write coordinates (write -1 to see map): ";
	std::cin >> p.x;
	if (p.x == -1)
	{
		std::cout << fld;
		addUnitChoise();
		return;
	}

	std::cin >> p.y;

	if (p.x < 0 || p.y < 0)
	{
		std::cout << "Try again\n\n";
		addUnitChoise();
		return;
	}
	readUnitType(p);
}

void Dialog::removeUnitChoise()
{
	Point p;
	std::cout << "Write coordinates: ";
	std::cin >> p.x;

	std::cin >> p.y;
	if (p.x < 0 || p.y < 0)
	{
		std::cout << "Try again\n\n";
		removeUnitChoise();
		return;
	}

	auto removeRes = fld.removeUnit(p);
	if (removeRes == addAndRemoveResult::removeErrorNoUnit)
	{
		std::cout << "Error. No unit\n\n";
	}
	else
	{
		std::cout << "Unit removed\n\n";
	}

}

void Dialog::writeUnitsLegend()
{
	for (auto& unit : unitsLegend)
	{
		std::cout << unit.first << " - " << unit.second << "\n";
	}
}

void Dialog::readUnitType(Point p)
{
	std::cout << "\nWrite units type (write h to see units legend): ";
	char c;
	std::cin >> c;
	std::cout << "\n";
	if (c == 'h')
	{
		writeUnitsLegend();
		readUnitType(p);
		return;
	}

	UnitBase* unitToAdd = nullptr;
	switch (c)
	{
	case 'A':
		unitToAdd = static_cast<UnitBase*>(new Archer());
		break;
	case 'R':
		unitToAdd = static_cast<UnitBase*>(new Rogue());
		break;
	case 'M':
		unitToAdd = static_cast<UnitBase*>(new Mage());
		break;
	case 'E':
		unitToAdd = static_cast<UnitBase*>(new Spearman());
		break;
	case 'N':
		unitToAdd = static_cast<UnitBase*>(new Shielder());
		break;
	case 'S':
		unitToAdd = static_cast<UnitBase*>(new Assasin());
		break;
	default:
		std::cout << "Incorrect type. Try again\n";
		readUnitType(p);
		return;
	}

	fld.addUnit(unitToAdd, p);
	std::cout << "Unit added\n\n";
}
