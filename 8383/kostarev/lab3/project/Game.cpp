#include <iostream>
#include "Game.h"
#include "Naming.h"

Game::Game() {
	std::cout << "You wan't start a game? (1 - yes, 0 - no)\t";
	std::cin >> gameOn;
	features = new Features();
	while (gameOn) {
		std::cout << "You want see a command panel?\t";
		std::cin >> seeCommands;
		if (seeCommands)
			features->printFeauters();
		nameCommand = features->getCommand();
		switch (nameCommand){
		case EXIT:
			command = nullptr;
			gameOn = false;
			break;
		case CREATE_BOARD:
			command = new NewBoard(&board);
			break;
		case CREATE_CITY_HALL:
			command = new NewCityHall(&board);
			break;
		case CREATE_BUILD:
			command = new NewBuild(&board);
			break;
		case DEL_BUILD:
			command = new DelBuild(&board);
			break;
		case ABOUT_BOARD:
			command = new AboutBoard(&board);
			break;
		case ABOUT_BUILD:
			command = new AboutBuild(&board);
			break;
		case ABOUT_CITY_HALL:
			command = new AboutCityHall(&board);
			break;
		case ABOUT_TREASURY:
			command = new AboutTreasury(&board);
			break;
		default:
			command = nullptr;
			std::cout << "I don't know this command" << std::endl;
			break;
		}
		if (command == nullptr) continue;
		if (command->execute()) {
			if (nameCommand == CREATE_CITY_HALL) features->cityHall = true;
			if (nameCommand == CREATE_BOARD) features->board = true;
			if (nameCommand == CREATE_BUILD) features->unit = true;
			if (nameCommand == DEL_BUILD && !board->getNumBuildings()) features->unit = false;
			std::cout << "Well" << std::endl;
		}
		else {
			std::cout << "THE COMMAND CAN'T BE EXECUTED" << std::endl;
		}
	}
	std::cout << "Ok, goodbye!" << std::endl;
}

Features::Features() {
	board = false;
	cityHall = false;
	unit = false;
}

Commands Features::getCommand() {
	int c;
	std::cout << "Your command:\t";
	std::cin >> c;
	return static_cast<Commands>(c);
}

void Features::printFeauters() {
	std::cout << "You can:" << std::endl;
	std::cout << "'0' - end game" << std::endl;
	if (board) {
		std::cout << "'11' - get info about board" << std::endl;
		std::cout << "'12' - get info about treasury" << std::endl;
	}
	else {
		std::cout << "'10' - create a board" << std::endl;
		return;
	}
	if (!cityHall) {
		std::cout << "'20' - create first City Hall" << std::endl;
		return;
	}
	else {
		std::cout << "'20' - create new City Hall" << std::endl;
		std::cout << "'21' - get info abou City Hall" << std::endl;
		std::cout << "'30' - create Building" << std::endl;
		if (!unit) return;
		std::cout << "'31' - get info about building" << std::endl;
		std::cout << "'32' - blow up a building" << std::endl;
	}
}

NewBoard::NewBoard(Board** board) {
	this->board = board;
}

bool NewBoard::execute() {
	std::cout << "Enter width and height of gameboard (5-49):\t";
	std::cin >> width >> height;
	if (width > 4 && width < 50 && height > 4 && height < 50) {
		*board = new Board(width, height);
		return true;
	}
	return false;
}

NewCityHall::NewCityHall(Board** board) {
	this->board = board;
}

bool NewCityHall::execute() {
	std::cout << "Enter x, y coordinates for building City Hall:\t";
	std::cin >> x >> y;
	if (x > (*board)->getWidth() || y > (*board)->getHeight() || x < 1 || y < 1) {
		return false;
	}
	(*board)->addCityHall(x, y);
	return true;
}

NewBuild::NewBuild(Board** board) {
	this->board = board;
}

bool NewBuild::execute() {
	std::cout << "Select a base (City Hall), enter x and y:\t";
	std::cin >> xBase >> yBase;
	if (xBase > (*board)->getWidth() || yBase > (*board)->getHeight() || xBase < 1 || yBase < 1 || !(*board)->isCityHall(xBase, yBase)) {
		return false;
	}
	std::cout << "Enter x, y coordinates for building:\t";
	std::cin >> x >> y;
	if (x > (*board)->getWidth() || y > (*board)->getHeight() || x < 1 || y < 1 || (x == xBase && y == yBase)) {
		return false;
	}
	std::cout << "Apartments: 0 - Dacha, 1 - Hrushchovka" << std::endl;
	std::cout << "Production: 2 - Ferma, 3 - Office" << std::endl;
	std::cout << "Services: 4 - Powerhouse, 5 - School, 6 - Vodokanal" << std::endl;
	std::cout << "Enter type of build:\t";
	std::cin >> type;
	return (*board)->addBuild(x, y, xBase, yBase, static_cast<Builds>(type));
}

DelBuild::DelBuild(Board** board) {
	this->board = board;
}

bool DelBuild::execute(){
	std::cout << "Enter x, y coordinates for blow up a building:\t";
	std::cin >> x >> y;
	if (x > (*board)->getWidth() || y > (*board)->getHeight() || x < 1 || y < 1 || (*board)->isCityHall(x, y)) {
		return false;
	}
	(*board)->delBuild(x, y);
	return true;
}

AboutBoard::AboutBoard(Board** board){
	this->board = board;
}

bool AboutBoard::execute() {
	std::cout << "Size: " << (*board)->getWidth() << "x" << (*board)->getHeight() << std::endl;
	(*board)->printBoard();
	std::cout << "Coins: " << (*board)->getCoin() << std::endl;
	std::cout << "Objects: " << (*board)->getNumObjects() << std::endl;
	return true;
}

AboutBuild::AboutBuild(Board** board) {
	this->board = board;
}

bool AboutBuild::execute() {
	std::cout << "Enter x, y coordinates of build:\t";
	std::cin >> x >> y;
	if (x > (*board)->getWidth() || y > (*board)->getHeight() || x < 1 || y < 1 || (*board)->isCityHall(x,y)){
		return false;
	}
	(*board)->printAboutCell(x, y);
	return true;
}

AboutCityHall::AboutCityHall(Board** board) {
	this->board = board;
}

bool AboutCityHall::execute() {
	std::cout << "Enter x, y coordinates of City Hall:\t";
	std::cin >> x >> y;
	if (x > (*board)->getWidth() || y > (*board)->getHeight() || x < 1 || y < 1 || !(*board)->isCityHall(x, y)) {
		return false;
	}
	(*board)->printAboutCell(x, y);
	return true;
}

AboutTreasury::AboutTreasury(Board** board){
	this->board = board;
}

bool AboutTreasury::execute() {
	std::cout << "Treasury: $" << (*board)->getCoin() << std::endl;
	return true;
}