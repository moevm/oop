#include "pch.h"
//#include <iostream>
#include "Map.h"
#include <Windows.h>
#include "Object.h"




Map::Map(int x, int y) { //конструктор
	count_object = 0;
	width = x;
	height = y;
	Object *line = new Object();
	Object* o = new Object(' ');
	field = new Object**[height + 2];
	for (int i = 0; i < height + 2; i++) {
		field[i] = new Object*[2 * width + 3];
		for (int j = 0; j < 2 * width + 3; j++) {
			if ((i == 0 || i == height + 1 || j == 0 || j == 2 * width + 2) && (j % 2 == 0)) field[i][j] = line;
			else field[i][j] = o;
		}
	}
}



Map::Map(Map&& map) : field(map.field)
{
	for (int i = 0; i < height + 2; i++)
		for (int j = 0; j < 2 * width + 3; j++)
			map.field[i][j] = nullptr;
}

Map::Map(const Map & map) { //конструктор копирования поля
	count_object = map.count_object;
	width = map.width;
	width = map.width;
	field = new Object**[height + 2];
	for (int i = 0; i < height + 2; i++)
		field[i] = new Object*[2 * width + 3];
	for (int i = 0; i < height + 2; i++)
		for (int j = 0; j < 2 * width + 3; j++)
			field[i][j] = map.field[i][j];
}

Map& Map::operator=(Map&& map)
{
	// Проверка на самоприсваивание
	if (&map == this)
		return *this;
	// Удаляем всё, что может хранить указатель до этого момента
	for (int i = 0; i < height + 2; i++) {
		delete field[i];
	}
	delete field;
	// Передаём право собственности на map.field в field
	field = map.field;
	for (int i = 0; i < height + 2; i++)
		for (int j = 0; j < 2 * width + 3; j++)
			map.field[i][j] = nullptr;
	return *this;
}

Map &Map::operator=(const Map &map) {//оператор для конструктора копирования
	if (&map == this)
		return *this;
	// Проверка на самоприсваивание
	Object* o = new Object(' ');
	// Удаляем всё, что может хранить указатель до этого момента
	for (int i = 0; i < height + 2; i++) {
		delete field[i];
	}
	delete field;
	// Копируем передаваемый объект
	field = new Object **[height + 2];
	for (int i = 0; i < height + 2; i++) {
		field[i] = new Object *[2 * width + 3];
		for (int j = 0; j < 2 * width + 3; j++) {
			field[i][j] = o;
		}

	}
	for (int k = 0; k < height + 2; ++k) {
		for (int i = 0; i < 2 * width + 3; ++i) {
			field[k][i] = map.field[k][i];
		}
	}
	return *this;
}

void Map::print_map() {
	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < 2 * width + 3; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), field[i][j]->color);
			cout << field[i][j]->object;
		}
		cout << endl;
	}
	cout << endl;
}

void Map::add_on_map(int x, int y, Object* object) {
	if (count_object >= MAX || count_object >= 32767) {//инвариант
		cout << "Превышено максимальное количество объектов на поле" << endl;
		exit;
	}
	else {
		for (int i = 1; i < height + 1; i++) {
			for (int j = 1; j < 2 * width + 2; j++) {
				if (i == y && j == 2 * x) field[i][j] = object;
				mas_x[count_object] = x;
				mas_y[count_object] = y;
			}
		}
		count_object++;
	}
}

void Map::remove_from_map(int x, int y) {
	Object* g = new Object('*');
	int c = g->colorLand::green;
	g->color = c;
	for (int i = 1; i < height + 1; i++)
		for (int j = 1; j < 2 * width + 2; j++) {
			if (i == y && j == 2 * x) {
				if (isObject(i,j)) {
					count_object--; //уменьшается только если там был объект, т.е не будет меньше 0, инвариант???????
					field[i][j] = g;
					mas_x[count_object] = 0;
					mas_y[count_object] = 0;
				}
			}
		}
}


bool Map::isObject(int x, int y)
{
	Object* o = new Object(' ');
	if (field[x][y]->object != o->object)
		return true;
	else
		return false;

}
//~*^
int Map::isLandscape(int x, int y)
{
	char list[] = { '~', '*', '^'};
	for (int i = 0; i < height + 2; i++)
		for (int j = 0; j < 2 * width + 4; j++)
			if (i == y && j == 2 * x)
				for (int t = 0; t < sizeof(list); t++)
				{
					if (i == 0 || j == 0 || j == (2 * width + 2) || i == (height + 1))
						return 4;
					if (field[i][j]->object == list[t])
						return t + 1;
				}	
	return 0;
}


//PTCR
int Map::isNeutral(int x, int y)
{
	char list[] = { 'P', 'T', 'C', 'R' };
	for (int i = 1; i < height + 1; i++)
		for (int j = 1; j < 2 * width + 2; j++)
			if (i == y && j == 2 * x)
				for (int k = 0; k < sizeof(list); k++)
					if (field[i][j]->object == list[k])
						return ++i;
	return 0;
}

/*new Object(list[i])*/
bool Map::isUnit(int x, int y)
{
	char list[] = { 'X', 'H', 'M', 'A', 'F', 'G', 'L' };
	for (int i = 1; i < height + 1; i++)
		for (int j = 1; j < 2 * width + 2; j++)
			if (i == y && j == 2 * x)
				for (int k = 0; k < sizeof(list); k++)
					if (field[i][j]->object == list[k])
						return true;
	return false;
}

bool Map::isBase(int x, int y)
{
	for (int i = 1; i < height + 1; i++)
		for (int j = 1; j < 2 * width + 2; j++)
			if (i == y && j == 2 * x)
				if (field[i][j]->object == 'B')
					return true;
		return false;
}


Map::~Map() { //деструктор
	for (int i = 0; i < height + 2; i++)
		delete field[i];
	delete field;
}