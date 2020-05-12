#pragma once
class Command;
class Base;
class Field;
class Adapter;

class Status {
public:
	virtual bool doCommand(Command * com, Base ** base) = 0;
};
class Status1 : public Status {
public:
	bool doCommand(Command * com, Base ** base);
};
class Status2 : public Status {
public:
	bool doCommand(Command * com, Base ** base);
};


class RuleBase {
protected:
	Field* field;
	Status* status1;
	Status* status2;
	Status* currentStatus;
	Adapter * adapter;
public:
	RuleBase();
	void changeStatus();
	virtual Field* startField(Adapter* adapter) = 0;
	virtual void doCommand(Command * com, Base ** base) = 0;


};
class Rule1 : public RuleBase {

public:
	Field* startField(Adapter* adapter);
	int lose(Field* field);
	void doCommand(Command * com, Base ** base);


};
class Rule2 : public RuleBase {
public:
	Field* startField(Adapter* adapter);
	int lose(Field* field);
	void doCommand(Command * com, Base ** base);

};