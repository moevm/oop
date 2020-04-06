#pragma once
#include "pch.h"
#include "Object.h"
//#include "Units.h"
#include <iostream>
#include "Units.h"
#define MAX 4000

using namespace std;

class MapBlock
{
public:
	int x; int y;
	MapBlock();
	Units *getUnit();
	void setUnit(Units *unit);
private:
	 Units *_unit;
};

class Iterator
{
public:
	int count = 0;
	Iterator(int width, int height);
	MapBlock **mas;
};



/*
class Iterator {
	int m_x, m_y;
	Units **mas = new Units *[m_x + 1];
	//Object **position = mas;
	int numb_elem = 0;
public:
	Iterator(int max_X, int max_Y);
	Units getPointer(int X, int Y);
	void setObject(int X, int Y, Units* unit);
	~Iterator();
	void setMemory();

};*/

class Map {
	int  width;   //размеры поля
	int  height;   //размеры поля
	int  count_object;//количество объектов
	int  mas_x[MAX];  //массив координат x элементов на поле
	int  mas_y[MAX];  //массив координат y элементов на поле
public:
	Iterator* iterator;
	Object ***field;    //само поле
	Map(int x, int y); //конструктор
	bool isObject(int x, int y);
	Map(const Map & map); //конструктор копирования поля
	Map &operator=(const Map &map);//оператор для конструктора копирования
	// Конструктор перемещения,
	// который передаёт право собственности на map.field в field
	Map(Map&& map);
	// Оператор присваивания перемещением,
	// который передаёт право собственности на map.field в field
	Map& operator=(Map&& map);
	void print_map();//выводит поле
	void add_on_map(int x, int y, Object* object);//добавляет объект
	void remove_from_map(int x, int y);//удаляет с поля объект
	int isLandscape(int x, int y);
	int isNeutral(int x, int y);
	bool isUnit(int x, int y);
	bool isBase(int x, int y);
	~Map();
};



