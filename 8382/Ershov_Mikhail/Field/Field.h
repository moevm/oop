//#pragma once
#ifndef FIELD_H
#define FIELD_H

//#include "Warrior.h"
#include "../Unit/Orcs.h"
#include "../Unit/Men.h"
#include "../Unit/Elfs.h"
#include "NeutralObject/NeutralObject.h"
//#include "Landscape.h"
#include "../Unit/UnitFactory.h"
#include "Cell.h"
#include "Landscape/Proxy.h"
#include "../Interfaces/Mediator.h"
//#include "Command.h"
#include "../Logging/LoggerProxy.h"
#include "../Base/Base.h"

class Proxy;
class Command;

using namespace std;

class Field {
public:
    // Конструкторы
	Field();
	Field(int a, int numOfUnitsOnEachSide, LoggerProxy* logger);

	// Деструктор
	~Field();

    // Конструктор копирования (lab1)
	Field(const Field& f);

    // Конструктор перемещения (lab1)
	Field(Field&& f);

	void mas(); // Создает двумерный массив cell's

	void print(int rule); // Печатает поле

	void init(int numOfOrcs, int numOfElfs, int numOfMens); // Инициализирует поле

    Warrior add(string& character, int coordx, int coordy); // Добавление юнита

	void moving(string& character, int direction); // Двигает юнит character в направление direction

	string check(string& character); // Проверка на то, в какакие направление может ходить юнит character

	void unitsSpecAbil(int dir, Warrior w, int x, int y);    //специальные возможности юнитов в атаке
	void del(string& character);          //удалить юнит
	void changeCell(string& valuee, int x, int y);      //поменять значение в клетке в координатах (x; y)
	bool isCellFree(int x, int y);       //пустая ли клетка в координатах (x; y)
	string getValueInCell(int x, int y);   //возвращает значение, хранящаеся в cell[x][y]
	Cell** getCell();            //возвращает клетку
	int howManyMoves(string character);       //возвращает количество шагов, которое можно сделать игроку
	void landscapeEffect();     //эффект "неизвестных земель"
	void neutObjEffect();      //эффект нейтральных объектов
	int getSizeOfField();    //возвращает размер поля
	void createBase(int x, int y, Base* base);	//создает на поле базу
	void setNewField(Cell** c);	//добавляет в поле новые клетки (нужно для загрузки игры)

private:
	int size; // Размер поля
	Cell** cell; // Двумерный массив клеток (поле)

	// Orcs
	Devourers dev; // Пожилатель
	Robbers rob; // Разбойник

    // Mens
	Spearman sp; // Копьеносец
	Wizard wiz; // Маг

	// Elfs
	Archer ar; // Лучник
	Invisible inv; // Невидимка

	int current1stPlayerUnits; // Текущее количество юнитов у 1-го игрока
	int current2ndPlayerUnits; // Текущее количество юнитов у 2-го игрока

	Mediator* med;
	LoggerProxy* logger;
};


#endif
