#pragma once

#include "Field.h"
#include "Base.h"

//#include "landscapeMapExample.h"

class Game
{
private:
	PlayingField* field;
	std::map<bool, Base*> bases;

public:
	Game(unsigned width, unsigned length, unsigned maxFieldObjects) {
		field = new PlayingField(width,length);
		field->setMaxNumberOfElements(maxFieldObjects);
		
		
		std::vector<char> mapExample_10x10 = {
'G', 'G', 'G', 'M', 'M', 'M','M', 'M', 'G','G',
'G', 'G', 'G', 'G', 'M', 'M','M', 'G', 'G','G',
'G', 'G', 'G', 'G', 'M', 'M','G', 'G', 'G','G',
'G', 'G', 'G', 'G', 'G', 'M','G', 'G', 'G','G',
'G', 'G', 'G', 'G', 'G', 'G','G', 'G', 'G','G',
'G', 'G', 'G', 'W', 'W', 'G','G', 'G', 'G','G',
'G', 'G', 'G', 'W', 'W', 'G','G', 'G', 'G','G',
'G', 'G', 'W', 'W', 'W', 'G','G', 'G', 'G','G',
'G', 'G', 'W', 'W', 'G', 'G','G', 'G', 'G','G',
'G', 'G', 'G', 'G', 'G', 'G','G', 'G', 'G','G',
		};

		std::vector<char> objects = {
'N', 'N', 'N', 'M', 'M', 'M','M', 'M', 'G','G',
'G', 'G', 'G', 'G', 'H', 'M','M', 'G', 'G','G',
'G', 'G', 'G', 'G', 'M', 'M','G', 'G', 'G','G',
'G', 'G', 'G', 'G', 'G', 'M','G', 'F', 'G','G',
'G', 'G', 'G', 'G', 'G', 'G','G', 'G', 'G','G',
'G', 'G', 'G', 'W', 'W', 'G','G', 'G', 'G','G',
'G', 'A', 'G', 'W', 'W', 'G','G', 'G', 'G','G',
'G', 'G', 'W', 'W', 'W', 'G','G', 'H', 'G','G',
'G', 'G', 'W', 'W', 'H', 'G','G', 'G', 'G','G',
'G', 'G', 'G', 'G', 'G', 'G','G', 'G', 'G','N',
		};
		field->setLandscape(mapExample_10x10);
		field->setObjects(objects);
	}

	void addBase(int row, int col,int maxUnits,bool curPlayer) {
		Base* base = new Base(maxUnits, field,row, col,curPlayer);
		if (!base->isAlive()) {
			delete base;
			return;
		}
		bases[curPlayer] = base;
	}

	bool addUnit(int row, int col, std::string unitType,std::string color, bool curPlayer) {
		if (bases[curPlayer]) {
			if (bases[curPlayer]->createUnit(unitType, color, row, col))
				return true;
		}
		return false;
	}

	bool moveUnit(int X_old, int Y_old, int X_new, int Y_new,bool curPlayer) {
		if (field->moveUnit(X_old, Y_old, X_new, Y_new, curPlayer))
			return true;
		return false;
	}

	bool attack(int X_old, int Y_old, int X_new, int Y_new, bool curPlayer){
		if (field->commitInteraction(X_old, Y_old, X_new, Y_new, curPlayer, true))
			return true;
		return false;
	}

	bool heal(int X_old, int Y_old, int X_new, int Y_new, bool curPlayer){
		if (field->commitInteraction(X_old, Y_old, X_new, Y_new, curPlayer, false))
			return true;
		return false;
	}

	bool isPlayerAlive(int curPlayer) {
		return bases[curPlayer]->isAlive();
	}

	void showField() {
		std::cout << "Field:\n"; field->showConsoleField(); std::cout << "\n";
		std::cout << "Landscape:\n"; field->showConsoleLandscape(); std::cout << "\n";
	}

	std::string getInfoAboutCell(unsigned row,unsigned col) { //in process
		std::string out = field->getInfoCell(row,col);
		out = "\n[Info about cell with coords X - " + std::to_string(row) + " Y - " + std::to_string(col) + "]\n" + out;

		return out;
	}


};

