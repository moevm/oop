#include <iostream>
#include <string>
#include <Windows.h>
#include "Field.h"
#include "Unit_types.h"
using namespace std;



int main() 
{
	string command;
	int W, H;
	//cout << "Input field size\n";
	W = 10; H = 10;
	Field field(W, H);
	Field field_save(W, H);
	
	WaterBase  * bas1 = field.getWater();
	FireBase * bas2 = field.getFire();

	bas1->setCommand("0 go right");
	//bas1->setCommand("0 go right");
	//bas1->setCommand("0 go right");
	//bas1->createCuirassiers(3);
	//bas1->setCommand("1 go right");
	//bas1->setCommand("1 attack 9 9");
	//bas1->createLongShooters(4);
	//bas1->setCommand("2 go down");
	//bas1->setCommand("2 attack 9 9");
	//bas2->printInfo();

	/*
	FieldIterator iter = field.begin();
	while (iter != field.end()) {
		cout << iter.operator*().unit->getHealth()  << " ";
		iter++;
	}cout  << endl;
	*///field.print();
	bool flip = true;
	while (1)
	{
		
		field.print();
		
		
		if (flip)
		{
			cout << "first team:";
			getline(cin, command, '\n');
			
			if(bas1->setCommand(command))
				flip = false;
		}
		else
		{
			cout << "second team:";
			getline(cin, command, '\n');
			
			if(bas2->setCommand(command))
				flip = true;
		}
		
		system("pause");
		system("cls");
	}
	
	return 0;
}