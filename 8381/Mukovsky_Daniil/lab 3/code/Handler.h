#pragma once
#include "ClientInput.h"
#include "Command.h"
class Handler
{
public:
	virtual Handler* setNext(Handler* handler) = 0;
	virtual ClientInput* handle(ClientInput* input) = 0;
};

class AbstractHandler : public Handler
{
private:
	Handler* next;
protected:
	GameFacade* gameFacade;
public:
	AbstractHandler(){
		next = nullptr;
	}
	Handler* setNext(Handler* next) {
		this->next = next;
		return next;
	}
	ClientInput* handle(ClientInput* input) {
		if (this->next) {
			return this->next->handle(input);
		}
		else
			return nullptr;
	}
};


class StartGame : public AbstractHandler {
public:
	StartGame(GameFacade* gameFacade) {
		this->gameFacade = gameFacade;
	}
	ClientInput* handle(ClientInput* input) {
		if (input->getClientCommand() == START_GAME) {

			Command* newGameCmd =new StartNewGameCommand(gameFacade, input);
			newGameCmd->execute();
			
			delete newGameCmd;
			return nullptr;
		}
		else return AbstractHandler::handle(input);
	}
};

class Attack : public AbstractHandler {
public:
	Attack(GameFacade* gameFacade) {
		this->gameFacade = gameFacade;
	}
	ClientInput* handle(ClientInput* input) {
		if (input->getClientCommand() == ATTACK) {
			Command* attackUnit = new AttackCommand(gameFacade, input);
			attackUnit->execute();

			return nullptr;
		}
		else return AbstractHandler::handle(input);
	}
};


class Heal : public AbstractHandler {
public:
	Heal(GameFacade* gameFacade) {
		this->gameFacade = gameFacade;
	}
	ClientInput* handle(ClientInput* input) {
		if (input->getClientCommand() == HEAL) {
			Command* healUnit = new HealCommand(gameFacade, input);
			healUnit->execute();

			return nullptr;
		}
		else return AbstractHandler::handle(input);
	}
};

class AddUnit : public AbstractHandler {
public:
	AddUnit(GameFacade* gameFacade) {
		this->gameFacade = gameFacade;
	}
	ClientInput* handle(ClientInput* input) {
		if (input->getClientCommand() == ADD_UNIT) {


			Command* addUnitCmd = new AddUnitCommand(gameFacade,input);
			addUnitCmd->execute();

			delete addUnitCmd;
			return nullptr;
		}
		else return AbstractHandler::handle(input);
	}
};

class MoveUnit : public AbstractHandler {
public:
	MoveUnit(GameFacade* gameFacade) {
		this->gameFacade = gameFacade;
	}
	ClientInput* handle(ClientInput* input) {
		if (input->getClientCommand() == MOVE) {

			Command* moveUnitCmd = new MoveCommand(gameFacade, input);
			moveUnitCmd->execute();

			delete moveUnitCmd;
			return nullptr;
		}
		else return AbstractHandler::handle(input);
	}
};

class GetInfo : public AbstractHandler {
public:
	GetInfo(GameFacade* gameFacade) {
		this->gameFacade = gameFacade;
	}
	ClientInput* handle(ClientInput* input) {
		if (input->getClientCommand() == GET_INFO) {


			Command* getInfoCmd = new GetInfoCommand(gameFacade, input);
			getInfoCmd->execute();

			delete getInfoCmd;

			return nullptr;
		}
		else return AbstractHandler::handle(input);
	}
};