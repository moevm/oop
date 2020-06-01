#pragma once
#include <string>

enum clientCommand { NOTHING,MOVE, ATTACK,GET_INFO,ADD_UNIT,HEAL,START_GAME};

class ClientInput {
private:
	unsigned clientCommand_;
	unsigned row;
	unsigned col;
	unsigned rowTo;
	unsigned colTo;
	unsigned maxUnits;
	std::string unitType;
	std::string color;

public:
	ClientInput() {
		clientCommand_ = NOTHING;
		row = 0;
		col = 0;
		rowTo = 0;
		colTo = 0;
		maxUnits = 0;
		unitType = "";
		color = "";
	}

	void setStart(unsigned row_, unsigned col_, unsigned maxUnits_) {
		clientCommand_ = START_GAME;
		row = row_;
		col = col_;
		maxUnits = maxUnits_;
	}

	void setAttack(unsigned row_, unsigned col_, unsigned rowTo_, unsigned colTo_) {
		clientCommand_ = ATTACK;
		row = row_;
		col = col_;
		rowTo = rowTo_;
		colTo = colTo_;
	}
	void setHeal(unsigned row_, unsigned col_, unsigned rowTo_, unsigned colTo_) {
		clientCommand_ = HEAL;
		row = row_;
		col = col_;
		rowTo = rowTo_;
		colTo = colTo_;
	}

	void setMove(unsigned row_, unsigned col_, unsigned rowTo_, unsigned colTo_) {
		clientCommand_ = MOVE;
		row = row_;
		col = col_;
		rowTo = rowTo_;
		colTo = colTo_;
	}

	void setAddUnit(unsigned row_, unsigned col_, std::string unitType_, std::string color_) {
		clientCommand_ = ADD_UNIT;
		row = row_;
		col = col_;
		unitType = unitType_;
		color = color_;
	}

	void setGetInfo(unsigned row_, unsigned col_) {
		clientCommand_ = GET_INFO;
		row = row_;
		col = col_;
	}

	unsigned getRow() {
		return row;
	}
	unsigned getCol() {
		return col;
	}
	unsigned getRowTo() {
		if (clientCommand_ == HEAL || clientCommand_ == ATTACK || clientCommand_ == MOVE)
			return rowTo;
		else
			return 0;
	}
	unsigned getColTo() {
		if (clientCommand_ == HEAL || clientCommand_ == ATTACK || clientCommand_ == MOVE)
			return colTo;
		else
			return 0;
	}
	std::string getUnitType() {
		if (clientCommand_ == ADD_UNIT)
			return unitType;
		else
			return "";
	}
	std::string getColor() {
		if (clientCommand_ == ADD_UNIT)
			return color;
		else
			return "";
	}
	unsigned getMaxUnits() {
		if (clientCommand_ == START_GAME)
			return maxUnits;
		else
			return 0;
	}
	unsigned getClientCommand() {
		return clientCommand_;
	}

};







/*class ClientInput
{
public:
	virtual clientCommand getClientCommand() = 0;
};








class MoveClientInput : public ClientInput 
{
private:
	unsigned row;
	unsigned col;
	unsigned rowTo;
	unsigned colTo;
public:
	MoveClientInput(unsigned row, unsigned col, unsigned rowTo, unsigned colTo):
		row(row), col(col),rowTo(rowTo),colTo(colTo)
	{}

	clientCommand getClientCommand() {
		return MOVE;
	}
	unsigned getRow() {
		return row;
	}
	unsigned getCol() {
		return col;
	}
	unsigned getRowTo() {
		return rowTo;
	}
	unsigned getColTo() {
		return colTo;
	}
};

class AttackClientInput : public ClientInput
{
private:
	unsigned  row;
	unsigned  col;
	unsigned rowTo;
	unsigned  colTo;
public:
	AttackClientInput(unsigned row, unsigned col, unsigned rowTo, unsigned colTo) :
		row(row), col(col), rowTo(rowTo), colTo(colTo)
	{}

	clientCommand getClientCommand() {
		return ATTACK;
	}
	clientCommand getClientCommand() {
		return ADD_UNIT;
	}
	unsigned getRow() {
		return row;
	}
	unsigned getCol() {
		return col;
	}
	unsigned getRowTo() {
		return rowTo;
	}
	unsigned getCol() {
		return colTo;
	}
};


class AddUnitClientInput : public ClientInput
{
private:
	unsigned row;
	unsigned col;
	std::string unitType;
	std::string color;
public:
	AddUnitClientInput(unsigned row, unsigned col, std::string unitType,std::string color) :
		row(row), col(col), unitType(unitType), color(color)
	{}

	clientCommand getClientCommand() {
		return ADD_UNIT;
	}
	unsigned getRow() {
		return row;
	}
	unsigned getCol() {
		return col;
	}
	std::string getUnitType() {
		return unitType;
	}
	std::string getColor() {
		return color;
	}
};

class GetInfoClientInput : public ClientInput
{
private:
	unsigned row;
	unsigned col;

public:
	GetInfoClientInput(unsigned row, unsigned col) :
		row(row), col(col)
	{}

	clientCommand getClientCommand() {
		return GET_INFO;
	}
	unsigned getRow() {
		return row;
	}
	unsigned getCol() {
		return col;
	}
};
class StartNewGameClientInput : public ClientInput
{
private:
	unsigned  row;
	unsigned  col;
	unsigned  maxUnits;
	//unsigned numbOfPlayers;
public:
	StartNewGameClientInput(unsigned row, unsigned col, unsigned maxUnits, unsigned numbOfPlayers) :
		row(row), col(col), maxUnits(maxUnits)
	{}

	clientCommand getClientCommand() {
		return START_GAME;
	}
	unsigned getRows() {
		return row;
	}
	unsigned getCols() {
		return col;
	}
	unsigned getMaxUnits() {
		return maxUnits;
	}
};
*/