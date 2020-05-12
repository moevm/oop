#pragma once
#include <iostream> 
class Field;
class Fread;
class Fwrite;
class Cell;
class Base;
class Adapter;
struct Point;
using namespace std;
class Snapshot {
public:
	Snapshot(Field* field, std::string mod);
	~Snapshot();

	void save();
	void load();
	

private:
	int width; 
	int height;
	int max_units;
	int countUnit;
	Base * base[2];
	Field* field;
	Adapter* adapter;
	Fread* fileRead;
	Fwrite* fileWrite;
	int w = 0, h = 0;
	int x, y, gold1, health1, gold2, health2;
	int team;
	string unitClass, unitSub;
	int serial, number;
	float  armor, attack, stamina;
	string landSprite, netralSprite;

	void loadUnit(string type, int number, int team, int serial, Point dir);

};
