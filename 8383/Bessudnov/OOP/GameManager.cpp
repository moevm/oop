#include "pch.h"
#include "GameManager.h"
#include "GameUtilities.h"
#include "GameVisualiser.h"
#include "GameField.h"
#include "GameUnits.h"
#include "NeutralObject.h"
#include "PlayerInput.h"
#include "GameBases.h"


GameManager::GameManager() {
	inputManager = new PlayerInput;

	gameField = new GameField("Map01.txt");
	gameUnits = new GameUnits(gameField->getFieldBorders(), gameField);
	objectsContainer = new NeutralObjectContainer("Objects01.txt");
	baseContainer = new GameBasesContainer(*gameField, *gameUnits);
	pickBases();


	visualiser = new GameVisualiser(*gameField, *gameUnits, *objectsContainer, *baseContainer);

	actionManager = new ActionManager(baseContainer, gameUnits, visualiser, gameField);


	gameCycle();
}


GameManager::~GameManager() {
	delete inputManager;
	delete gameField;
	delete gameUnits;
	delete visualiser;
	delete objectsContainer;
	delete baseContainer;
}

void GameManager::gameCycle() {
	char messageCommand;
	for (;;) {
		inputManager->readInput(messageCommand);

		if (actionManager->action(messageCommand) == -1) {
			break;
		}

		//very very very bad
		neutralObjectExec();

		visualiser->update(*gameField, *gameUnits, *objectsContainer, *baseContainer);
	}
}

void GameManager::neutralObjectExec() {
	if (*objectsContainer == *gameUnits) {
		objectsContainer->useObject(*gameUnits);
	}
}

void GameManager::pickBases() {
	for (int i = 0; i < 3; i++) {
		switch (std::stoi(inputManager->readString("Pick base: "))) {
		case GameBaseTypes::One:
			baseContainer->bases.push_back(new OneBase(gameUnits));
			break;
		case GameBaseTypes::Two:
			baseContainer->bases.push_back(new TwoBase(gameUnits));
			break;
		case GameBaseTypes::Three:
			baseContainer->bases.push_back(new ThreeBase(gameUnits));
			break;
		case GameBaseTypes::Four:
			baseContainer->bases.push_back(new FourBase(gameUnits));
			break;
		} 

		int x;
		int y;
		x = std::stoi(inputManager->readString("Set x: "));
		GameUtilities::clamp(x, gameField->fieldProps.dimensions.x - 1, 0);
		if (x == gameField->fieldProps.dimensions.x - 1) {
			y = std::stoi(inputManager->readString("Set y: "));
		} else {
			std::cout << "y component was forced to be " << gameField->fieldProps.dimensions.y - 1 << std::endl;
			y = gameField->fieldProps.dimensions.y - 1;
		}

		baseContainer->bases.back()->location = Vector2D(x, y);
	}
}

UnitCommander::~UnitCommander() {
	delete unitsContainer;
}

int UnitCommander::doAction(char action) {
	switch (action) {
	case EXIT_COMMAND:
		output("EXIT");
		break;
	case NEXT_UNIT_COMMAND:
		command = new NextUnitCommand(unitsContainer, 1);
		command->execute();
		output("NEXT UNIT");
		break;
	case PREV_UNIT_COMMAND:
		command = new NextUnitCommand(unitsContainer, 0);
		command->execute();
		output("PREV UNIT");
		break;
	case MOVE_UP_COMMAND:
		command = new MoveUnitCommand(unitsContainer, Vector2D(0, -1));
		command->execute();
		output("MOVE UP");
		break;
	case MOVE_DAWN_COMMAND:
		command = new MoveUnitCommand(unitsContainer, Vector2D(0, 1));
		command->execute();
		output("MOVE DAWN");
		break;
	case MOVE_LEFT_COMMAND:
		command = new MoveUnitCommand(unitsContainer, Vector2D(-1, 0));
		command->execute();
		output("MOVE LEFT");
		break;
	case MOVE_RIGTH_COMMAND:
		command = new MoveUnitCommand(unitsContainer, Vector2D(1, 0));
		command->execute();
		output("MOVE RIGTH");
		break;
	case ATTACK_COMMAND:
		command = new ActionUnitCommand(unitsContainer);
		command->execute();
		output("ATTACK");
		break;
	default:
		return 0;
	}

	return 1;
}

BaseCommander::~BaseCommander() {
	delete baseContainer;
}

int BaseCommander::doAction(char action) {
	switch (action) {
	case NEXT_BASE_COMMAND:
		command = new NextBaseCommand(baseContainer, 1);
		command->execute();
		output("NEXT BASE");
		break;
	case PREV_BASE_COMMAND:
		command = new NextBaseCommand(baseContainer, 0);
		command->execute();
		output("PREV BASE");
		break;
	case SPAWN_COLLECTOR:
		command = new SpawnUnitCommand(baseContainer, SPAWN_COLLECTOR);
		command->execute();
		output("SPAWN COLLECTOR");
		break;
	case SPAWN_SPRINKLER:
		command = new SpawnUnitCommand(baseContainer, SPAWN_SPRINKLER);
		command->execute();
		output("SPAWN SPRINKLER");
		break;
	case SPAWN_UNIT01:
		command = new SpawnUnitCommand(baseContainer, SPAWN_UNIT01);
		command->execute();
		output("SPAWN UNIT01");
		break;
	case SPAWN_UNIT02:
		command = new SpawnUnitCommand(baseContainer, SPAWN_UNIT02);
		command->execute();
		output("SPAWN UNIT02");
		break;
	case SPAWN_UNIT03:
		command = new SpawnUnitCommand(baseContainer, SPAWN_UNIT03);
		command->execute();
		output("SPAWN UNIT03");
		break;
	default:
		return 0;
	}

	return 1;
}

ActionManager::~ActionManager() {
	delete baseCommander;
	delete unitCommander;
	delete gameFlowCommander;
}

int ActionManager::action(char action) {
	if (baseCommander->doAction(action) == 1) {
		return 1;
	}

	if (unitCommander->doAction(action) == 1) {
		return 1;
	}

	if (gameFlowCommander->doAction(action) == -1) {
		return -1;
	}

	return 1;
}

int GameFlowCommander::doAction(char action) {
	switch (action) {
	case EXIT_COMMAND:
		output("EXIT");
		break;
	default:
		output("WRONG");
		return 0;
	}

	return -1;
}

void Commander::output(std::string message) {
	gameVis->printMessage(message, WAIT_TIME);
}

Commander::~Commander() {
	delete gameVis;
}
