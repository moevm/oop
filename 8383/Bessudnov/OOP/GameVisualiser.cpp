#include "pch.h"
#include "GameVisualiser.h"
#include "GameUtilities.h"
#include "NeutralObject.h"
#include "GameBases.h"
#include "GameField.h"
#include "GameUnits.h"



GameVisualiser::GameVisualiser(GameField &field, GameUnits &units, NeutralObjectContainer &objCon, GameBasesContainer &bases) {
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	initCommands();
	update(field, units, objCon, bases);
}


GameVisualiser::~GameVisualiser() {

}

void GameVisualiser::update(GameField &field, GameUnits &units, NeutralObjectContainer &objCon, GameBasesContainer &bases) {
	system("cls");
	for (int i = 0; i < field.fieldProps.dimensions.y; i++) {
		for (int j = 0; j < field.fieldProps.dimensions.x; j++) {
			if (!drawUnit(units, Vector2D(j, i)) && !drawObj(objCon, Vector2D(j, i)) && !drawBase(bases, Vector2D(j, i))) {
				SetConsoleTextAttribute(console, field.fieldProps.blocks[j][i]->blockType);
				std::cout << field.fieldProps.blocks[j][i]->blockType;
			}
			SetConsoleTextAttribute(console, 0);
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	printBases(bases);
	printUnits(units);
	printCommands();
}

void GameVisualiser::printUnits(GameUnits& units) {
	SetConsoleTextAttribute(console, 6);
	std::cout << "UNITS" << std::endl;
	std::cout << std::endl;
	for (auto &unit : units.units) {
		if (unit->unitProps.isActive) {
			std::cout << ">> ";
		}
		std::cout << unit->unitProps.type << " (";
		std::cout << unit->unitProps.location.x << ",";
		std::cout << unit->unitProps.location.y << ") ";
		std::cout << "dew: " << unit->unitProps.dew.parameterValueCurrent << " ";
		std::cout << "ligth: " << unit->unitProps.ligth.parameterValueCurrent << " ";
		std::cout << "moves: " << unit->unitProps.moves.parameterValueCurrent << " ";
		std::cout << "damage: " << unit->unitProps.damage.parameterValueCurrent << " ";
		std::cout << "sugar: " << unit->unitProps.sugar.parameterValueCurrent << std::endl;
	}
	std::cout << std::endl;
}

void GameVisualiser::printBases(GameBasesContainer &bases) {
	SetConsoleTextAttribute(console, 12);
	std::cout << std::endl;
	std::cout << "BASES" << std::endl;
	for (auto &base : bases.bases) {
		if (base->isActive) {
			std::cout << ">> ";
		}
		std::cout << "Type: "<< base->type << std::endl;
		for (auto &units : base->baseUnits) {
			for (auto &unit : units->units) {
				if (unit != nullptr) {
					std::cout << "	";
					if (unit->unitProps.isActive) {
						std::cout << "> ";
					}
					std::cout << "Unit type: " << unit->unitProps.type;
					std::cout << std::endl;
				}
			}
		}
	}
}

void GameVisualiser::printMessage(std::string message, int delay) {
	SetConsoleTextAttribute(console, 7);
	std::cout << message << std::endl;
	Sleep(delay);
}

void GameVisualiser::printCommands() {
	std::cout << "COMMANDS" << std::endl;

	for (commandsIt = commands.begin(); commandsIt != commands.end(); commandsIt++) {
		std::cout << commandsIt->first << "---" << commandsIt->second << std::endl;
	}
}

void GameVisualiser::initCommands() {
	std::ifstream ifs;
	ifs.open("controls.txt", std::ifstream::in);

	std::string inputS;
	char inputC;
	while (ifs >> inputS && ifs >> inputC) {
		commands[inputS] = inputC;
	}

	ifs.close();
}

bool GameVisualiser::drawObj(NeutralObjectContainer &objCon, Vector2D loc) {
	NeutralObject *curObj;
	curObj = nullptr;

	curObj = objCon.getObjectAtLocation(loc);
	if (curObj != nullptr) {
		SetConsoleTextAttribute(console, 5 | BACKGROUND_INTENSITY);
		std::cout << curObj->type;
		return true;
	}
	return false;
}

bool GameVisualiser::drawUnit(GameUnits &units, Vector2D loc) {
	UnitParent *curUnit;
	curUnit = nullptr;

	curUnit = units.getUnit(loc);
	if (curUnit != nullptr) {
		SetConsoleTextAttribute(console, 6);
		std::cout << curUnit->unitProps.type;
		return true;
	}
	return false;
}

bool GameVisualiser::drawBase(GameBasesContainer &bases, Vector2D loc) {
	GameBase *curBase;
	curBase = nullptr;

	curBase = bases.getBaseAtLocation(loc);
	if (curBase != nullptr) {
		SetConsoleTextAttribute(console, 12);
		std::cout << curBase->type;
		return true;
	}
	return false;
}
