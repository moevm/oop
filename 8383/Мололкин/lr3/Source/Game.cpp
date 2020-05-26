#include "Game.h"



Game::Game()
{
	int length;
	int width;
	std::cout << "Game starts!" << std::endl;
	std::cout << "Enter board length and width" << std::endl;
	std::cin >> length;
	std::cin >> width;
	while (length > 30 || length < 10 || width > 30 || width < 10) {
		std::cerr << "Error with board size" << std::endl;
		std::cout << "Enter board length and width" << std::endl;
		std::cin >> length;
		std::cin >> width;
	}
	board = new GameBoard(length, width);
}

void printComands() {
	std::cout << "1 - Restart game" << std::endl;
	std::cout << "2 - Print board" << std::endl;
	std::cout << "3 - Move unit" << std::endl;
	std::cout << "4 - Print information about base" << std::endl;
	std::cout << "5 - Create unit from base" << std::endl;
	std::cout << "6 - Print information about unit" << std::endl;
	std::cout << "7 - Attack unit or base" << std::endl;
	std::cout << "All other numbs and symbols - Stop game" << std::endl;
}

void Game::startGame()
{
	Command* command;
	bool isGameGoing = true;
	while (isGameGoing) {
		printComands();
		int comandNum;
		std::cin >> comandNum;
		switch (comandNum)
		{
		case 1:
			command = new RestartCommand(&board);
			break;
		case 2:
			command = new PrintBoardCommand(&board);
			break;
		case 3:
			command = new MoveUnitCommand(&board);
			break;
		case 4:
			command = new AboutBaseCommand(&board);
			break;
		case 5:
			command = new CreateUnitFromBaseCommand(&board);
			break;
		case 6:
			command = new AboutUnitCommand(&board);
			break;
		case 7:
			command = new UnitAttackCommand(&board);
			break;
		default:
			command = nullptr;
			isGameGoing = false;
			break;
		}
		if (!isGameGoing) break;
		if (command != nullptr && command->execute()) {
			std::cout << "The command was executed without problems" << std::endl;
		}
		else std::cout << "The command wasn't executed" << std::endl;
	}
	std::cout << "Game was finished" << std::endl;
}

PrintBoardCommand::PrintBoardCommand(GameBoard** board)
{
	this -> board = board;
}

bool PrintBoardCommand::execute()
{
	for (int i = 0; i < (*board)->getLength(); i++) {
		if (i < 10) std::cout << i << " |";
		else std::cout << i << "|";
		std::cout << (*board)->getLine(i);
		std::cout << std::endl;
	}
	std::cout << "  ";
	for (int i = 0; i < (*board)->getWidth(); i++)
	{
		if (i + 1 < 10) std::cout << "   " << i << "    ";
		else if (i == 9) std::cout << "  " << i;
		else std::cout << "      " << i;
	}
	std::cout << std::endl;
	std::cout << "---";
	for (int i = 0; i < (*board)->getWidth(); i++)
	{
		std::cout << "----";
	}
	std::cout << std::endl;
	return true;
}


RestartCommand::RestartCommand(GameBoard** board)
{
	this->board = board;
}

bool RestartCommand::execute()
{
	int length;
	int width;
	std::cout << "Game starts!" << std::endl;
	std::cout << "Enter board length and width" << std::endl;
	std::cin >> length;
	std::cin >> width;
	while (length > 30 || length < 10 || width > 30 || width < 10) {
		std::cerr << "Error with board size" << std::endl;
		std::cout << "Enter board length and width" << std::endl;
		std::cin >> length;
		std::cin >> width;
	}
	*board = new GameBoard(length, width);
	return true;
}

MoveUnitCommand::MoveUnitCommand(GameBoard** board)
{
	this->board = board;
}

bool MoveUnitCommand::execute()
{
	std::cout << "Enter coordinates of unit, and coordinates where to move unit" << std::endl;
	int coordX1, coordY1, coordX2, coordY2;
	std::cin >> coordY1 >> coordX1 >> coordY2 >> coordX2;
	return (*board)->moveUnit(std::pair<int, int>(coordX1, coordY1), std::pair<int, int>(coordX2, coordY2));
}

AboutBaseCommand::AboutBaseCommand(GameBoard** board)
{
	this->board = board;
}

bool AboutBaseCommand::execute()
{
	std::cout << "Enter base number 1 or 2" << std::endl;
	int baseNumber;
	std::cin >> baseNumber;
	Base* base;
	if(baseNumber == 1)
		base = (*board)->getBase1();
	else if(baseNumber == 2)
		base = (*board)->getBase2();
	else return false;
	std::cout << "Base information:" << std::endl;
	std::cout << "Team: " << base->getBaseNum() << std::endl;
	std::cout << "Posittion: (" << base->getX() << "," << base->getY() << ")" << std::endl;
	std::cout << "Health: " << base->getHealth() << std::endl;
	std::cout << "Number units from base: " << base->getNumUnitsFromBase() << std::endl;
	return true;
}

AboutUnitCommand::AboutUnitCommand(GameBoard** board)
{
	this->board = board;
}

bool AboutUnitCommand::execute()
{
	std::cout << "Enter coordinates of unit" << std::endl;
	int coordX, coordY;
	std::cin >> coordY >> coordX;
	IUnit* unit = (*board) -> getBoard()[coordX][coordY] -> getUnitOnCell() ;
	if (unit == nullptr) return false;
	std::cout << "Team: " << unit->getTeam() << std::endl;
	std::cout << "Health: " << unit->getHealth() << std::endl;
	std::cout << "Armour: " << unit->getArmour() << std::endl;
	std::cout << "Attack: " << unit->getAttack() << std::endl;
	return true;
}

CreateUnitFromBaseCommand::CreateUnitFromBaseCommand(GameBoard** board)
{
	this->board = board;
}

bool CreateUnitFromBaseCommand::execute()
{
	std::cout << "Enter base number 1 or 2" << std::endl;
	int baseNumber;
	std::cin >> baseNumber;
	if (!(baseNumber == 1 || baseNumber == 2)) return false;
	std::cout << "Choose unit type" << std::endl;
	std::cout << "1 - Spearman" << std::endl;
	std::cout << "2 - Swordsman" << std::endl;
	std::cout << "3 - Archer" << std::endl;
	std::cout << "4 - Ballista" << std::endl;
	std::cout << "5 - Crossbowman" << std::endl;
	std::cout << "6 - Catapult" << std::endl;
	int unitNumber;
	std::cin >> unitNumber;
	if (unitNumber < 1 && unitNumber > 6) return false;
	Units unitType = static_cast<Units>(unitNumber);
	std::cout << "Enter unit possition" << std::endl;
	int coordX, coordY;
	std::cin >> coordY >> coordX;
	(*board)->createUnit(baseNumber, unitType, std::pair<int, int>(coordX, coordY));
	return true;
}

UnitAttackCommand::UnitAttackCommand(GameBoard** board)
{
	this->board = board;
}

bool UnitAttackCommand::execute()
{
	Mediator* mediator = new AttackMediator();
	std::cout << "Enter coordinates attacker and attacked";
	int coordX1, coordY1, coordX2, coordY2;
	std::cin >> coordY1 >> coordX1 >> coordY2 >> coordX2;
	IUnit* attacker;
	if (!(*board)->getBoard()[coordX1][coordY1]->getEmptyOfCell() && (*board)->getBoard()[coordX1][coordY1]->getIsUnitOnCell()) attacker = (*board)->getBoard()[coordX1][coordY1]->getUnitOnCell();
	else return false;
	if (!(*board)->getBoard()[coordX2][coordY2]->getEmptyOfCell()) {
		if ((*board)->getBoard()[coordX2][coordY2]->getIsUnitOnCell())
			mediator->attackUnit(attacker->getAttack(), (*board)->getBoard()[coordX2][coordY2]->getUnitOnCell());
		else mediator->attackBase(attacker->getAttack(), (*board)->getBoard()[coordX2][coordY2]->getBaseOnCell());
		return true;
	}
	else return false;
}