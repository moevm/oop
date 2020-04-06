#pragma once
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <map>

class GameField;
class GameUnits;
class NeutralObjectContainer;
class GameBasesContainer;
class Vector2D;

class GameVisualiser {
public:
	GameVisualiser(GameField &field, GameUnits &units, NeutralObjectContainer &objCon, GameBasesContainer &bases);
	~GameVisualiser();

	void update(GameField &field, GameUnits &units, NeutralObjectContainer &objCon, GameBasesContainer &bases);
	void printUnits(GameUnits &units);
	void printBases(GameBasesContainer &bases);
	void printMessage(std::string message, int delay);
	void printCommands();
private:
	HANDLE console;
	std::map<std::string, char> commands;
	std::map<std::string, char>::iterator commandsIt;

	void initCommands();

	bool drawObj(NeutralObjectContainer &objCon, Vector2D loc);
	bool drawUnit(GameUnits &units, Vector2D loc);
	bool drawBase(GameBasesContainer &bases, Vector2D loc);
};

