#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Field.h"
#include "UnitTypeDistance.h"
#include "UnitTypeStealth.h"
#include "UnitTypeWarrior.h"
#include <map>

struct Dialog
{
	Dialog()
	{
		options.push_back("1) Create field\n");
		options.push_back("2) Add unit\n");
		options.push_back("3) Remove unit\n");
		options.push_back("4) Show field\n");
		options.push_back("5) Quit\n");

		unitsLegend['A'] = "Archer";
		unitsLegend['M'] = "Mage";
		unitsLegend['E'] = "Spearman";
		unitsLegend['S'] = "Shielder";
		unitsLegend['N'] = "Assasin";
		unitsLegend['R'] = "Rogue";
	}
	void start();
	void speak();
	void createFieldChoise();
	void addUnitChoise();
	void removeUnitChoise();
	void writeUnitsLegend();
	void readUnitType(Point p);

private:
	std::string greeting = "Hello! I don't know how to do anything, but tasks for lr1 are working, so ";
	std::string chooseOption = "choose option:\n";
	std::vector<std::string> options;
	std::string choiseRequest = "I think you have enough time to think so write your choise: ";
	Field fld;
	std::map<char, std::string> unitsLegend;
};

