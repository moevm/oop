//#pragma once
#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <vector>
//#include "Warrior.h"
#include "Field.h"
#include "BaseIObserver.h"
#include "BaseFlyWeight.h"

class Base : public IObserver{
public:
	Base(int size, char type, LoggerProxy* logger);
	~Base();
	void createOrcsBase(int G, Field& f1);   //по умолчанию спавнит орков разбойников
	void addInOrcsBase(string& character, Field& f1, int G);
	void createMEBase(int G, Field& f1); //по умолчанию спавнит эльфов лучников
	void addInMEBase(string& character, Field& f1, int G);
	void updateNotify(Subject* s) override;
	void printBaseCondition();      //печать состояния базы
	char getTypeOfBase();
	void attackOnBase(int x, int y, int damage, Field& field);
	int getCurrentOrcsNum();
	int getCurrentMEnum();
	int getBaseHealth();
	void setOrcsUnits(vector <Warrior> orcs);
	void setMEUnits(vector <Warrior> ME);
	void setHealth(int hp);
	vector <Warrior> getOrcsUnits();
	vector <Warrior> getMEUnits();

private:
	vector <Warrior> vOrcs;
	vector <Warrior> vME;
	char typeOfBase;   // 'o' - база орков, 'm' - база людей и эльфов
	int sizeOfField;
	int baseHealth;
	int max;
	int currentOrcsNum;
	int currentMEnum;
	FlyweightUnitFactory fuf;
	LoggerProxy* logger;
};

#endif