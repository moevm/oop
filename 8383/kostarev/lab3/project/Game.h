#pragma once
#include "GameBoard.h"
#include "Naming.h"

class Features {
public:
	bool board;
	bool cityHall;
	bool unit;
	Features();
	Commands getCommand();
	void printFeauters();
};

class Command {
protected:
	Board** board;
public:
	virtual bool execute() = 0;
};

class Game{
private:
	Board* board;
	Command* command;
	Commands nameCommand;
	Features* features;
	bool seeCommands;
	bool gameOn;
public:
	Game();
};

class NewBoard :public Command {
private:
	int width, height;
public:
	NewBoard(Board** board);
	bool execute() override;
};

class NewCityHall : public Command {
private:
	int x, y;
public:
	NewCityHall(Board** board);
	bool execute() override;
};

class NewBuild : public Command {
private:
	int x, y, type, xBase, yBase;
public:
	NewBuild(Board** board);
	bool execute() override;
};

class DelBuild : public Command {
private:
	int x, y;
public:
	DelBuild(Board** board);
	bool execute() override;
};

class AboutBoard :public Command {
public:
	AboutBoard(Board** board);
	bool execute() override;
};

class AboutBuild : public Command {
private:
	int x, y;
public:
	AboutBuild(Board** board);
	bool execute() override;
};

class AboutCityHall : public Command {
private:
	int x, y;
public:
	AboutCityHall(Board** board);
	bool execute() override;
};

class AboutTreasury : public Command {
public:
	AboutTreasury(Board** board);
	bool execute() override;
};