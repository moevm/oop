#pragma once
#include <iostream>
#include <utility>
#include "GameBoard.h"
#include "IUnit.h"
#include "Mediator.h"

class Game
{
private:
	GameBoard* board;

public:
	Game();
	void startGame();
};


class Command
{
public:
	virtual bool execute() = 0;
};

class UnitAttackCommand : public Command
{
private:
	GameBoard** board;
public:
	UnitAttackCommand(GameBoard** board);
	bool execute() override;
};


class RestartCommand : public Command
{
private:
	GameBoard** board;
public:
	RestartCommand(GameBoard** board);
	bool execute() override;
};

class PrintBoardCommand : public Command
{
private:
	GameBoard** board;
public:
	PrintBoardCommand(GameBoard** board);
	bool execute() override;
};

class MoveUnitCommand : public Command
{
private:
	GameBoard** board;
public:
	MoveUnitCommand(GameBoard** board);
	bool execute() override;
};

class AboutBaseCommand : public Command
{
private:
	GameBoard** board;
public:
	AboutBaseCommand(GameBoard** board);
	bool execute() override;
};

class CreateUnitFromBaseCommand : public Command
{
private:
	GameBoard** board;
public:
	CreateUnitFromBaseCommand(GameBoard** board);
	bool execute() override;
};

class AboutUnitCommand : public Command
{
private:
	GameBoard** board;
public:
	AboutUnitCommand(GameBoard** board);
	bool execute() override;
};


