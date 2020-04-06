#pragma once
#include <iostream>
#include "Commands.h"

#define WAIT_TIME 1000

class GameUnits;
class PlayerInput;
class GameField;
class GameVisualiser;
class Vector2D;
class NeutralObjectContainer;
class GameBasesContainer;


class Commander {
private:
	GameVisualiser *gameVis;
protected:
	void output(std::string message);
public:
	Commander(GameVisualiser *gameVis) : gameVis(gameVis) {}

	~Commander();

	virtual int doAction(char action) = 0;
};

class UnitCommander : public Commander {
private:
	GameUnits *unitsContainer;

	UnitCommands *command;

public:
	UnitCommander(GameUnits *unitsContainer, GameVisualiser *gameVis) : 
		unitsContainer(unitsContainer), Commander(gameVis) {}

	~UnitCommander();

	int doAction(char action);
};

class BaseCommander : public Commander {
private:
	GameBasesContainer *baseContainer;
	
	BaseCommands *command;

public:
	BaseCommander(GameBasesContainer *baseContainer, GameVisualiser *gameVis) : 
		baseContainer(baseContainer), Commander(gameVis) {}

	~BaseCommander();

	int doAction(char action);
};

class GameFlowCommander : public Commander {
public:
	GameFlowCommander(GameVisualiser *gameVis) : Commander(gameVis) {}

	int doAction(char action);
};

class ActionManager {
private:
	BaseCommander *baseCommander;
	UnitCommander *unitCommander;
	GameFlowCommander *gameFlowCommander;
	GameField *gameField;
public:
	ActionManager(GameBasesContainer *baseContainer, GameUnits *unitsContainer, GameVisualiser *gameVis, GameField *field) 
		: gameField(field) {
		baseCommander = new BaseCommander(baseContainer, gameVis);
		unitCommander = new UnitCommander(unitsContainer, gameVis);
		gameFlowCommander = new GameFlowCommander(gameVis);
	}

	~ActionManager();

	int action(char action);
};

class GameManager {
public:
	GameManager();
	~GameManager();
	NeutralObjectContainer *objectsContainer;
	GameUnits *gameUnits;
	PlayerInput *inputManager;
	GameField *gameField;
	GameVisualiser *visualiser;
	GameBasesContainer *baseContainer;
	ActionManager *actionManager;

protected:
	void gameCycle();
	void unitMove(Vector2D direction);
	void neutralObjectExec();

	void pickBases();

};


