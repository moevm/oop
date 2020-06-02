#pragma once
#include "factory.h"
#include "Object.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "Map.h"
#include "Units.h"
#include "Iterator.h"
#include "Neutral.h"
#include "Adapter.h"


/*!
\brief Класс Базы

Класс служит для создания базы, инициализации ресурсов, создания и контролирования юнитов.
Также в нем хранится информация о текущем состоянии базы и юнитов.
*/

class Bases : public Factory, public Object{
	
/*!
\brief Перечисление доступных юнитов

Перечисление содержит информацию о доступных юнитах и их индексацию
Маг: 1, Целитель: 2, Лучник: 3, Арбалетчик: 4, Мечник: 5, Рыцарь: 6
*/
	enum allClasses
	{
		magician = 1, healer, archer, arbalester, swordsman, spear
	};
/*!
\brief Структура координат базы

Содержит информацию о текучщем положение базы в простарнстве на карте
*/
	struct Coordinates {
		int x, y;
	}XY;
/// Наименование юнитов
	string units[7] = { "test", "magician", "healer", "archer", "arbalester", "swordsman", "spear" };
/// Количество оставшихся приказов
	int _move_count; 
/// Максимальное количество приказов
	int _move_count_max; 
/// Стартовое количество ресурсов
	int _resources; 
/// Стоимость создания арбалетчика
	int _cost_arbalester = 1; 
/// Стоимость создания лучника
	int _cost_archer = 2; 
/// Стоимость создания мечник
	int _cost_swordsman = 1; 
/// Стоимость создания рыцаря
	int _cost_spear = 2; 
/// Стоимость создания целителя
	int _cost_healer = 2; 
/// Стоимость создания мага
	int _cost_magician = 3; 
protected:
/// Обозначение базы на карте
	char name; 
/// Количество особого ресурса
	int ester;
/// Количество HP базы
	int health; 
/// Состояния активации щита
	bool shild = false; 
/// Состояние поддержки флота
	bool fleet = false; 
public:
/// Функция, обновляющая количество оставшихся приказов после завершения хода 
	void refresh(); 
/// Итератор юнитов
	Iterator *iterat; 
/*!
\brief Функция, вовращающая всех юнитов в обычном режиме
\param *adapter Адаптер для логирования действий базы
\return Массив доступных юнитов
*/
	Units **getAllUnits(Adapter *adapter); 
/*!
\brief Функция, возвращающая всех юнитов в режиме загрузки сохранения
\return Массив доступных юнитов
*/
	Units **getAllUnits(); 
/*!
\brief Функция установки текущего положения базы
\param x,y Координаты по оси X и оси Y
*/
	void setLoc(int x, int y); 
/*!
\brief Функция установки наименования базы
\param n Символьное обозначение на карте
*/
	void setName(char n);
	/// Функция установки цвета базы (завизит от количества игроков)
	void setColor(int c); 
	/// Функция установки количества HP базы
	void setHealth(int h); 
	/// Функция установки количества особого ресурса 
	void setEster(int est); 
	/// Получение ссылки на конкретного юнита
	Units *getLink(int pos); 
	/// Количество юнитов
	int count_units = 0; 
	/// Клекта производства базы
	int X, Y; 
/*!
\brief Конструктор Базы
\param pos_x,pos_y Координаты базы
\param N,col,health,move_count Наименование базы, её цвет, количество HP и максимальное количество приказов за ход
\param *adapter Адаптер для логирования действий базы

В конструкторе происходит инициализация важных атрибутов Базы. Происходит инициализация ресурсов

*/
	Bases(int pos_x, int pos_y, char N, int col, int health, int res, int move_count, Adapter *adapter);  
/// Функция производства юнитов
	void production(int select, Map *field, Creating *neutral, Adapter *adapter); 
/// Функция инициализации начальных ресурсов
	void initialization(int resources, Adapter *adapter); 
/// Переопределяемая функция создания мечника
	Swordsman* createSwordsman(Map *field, Creating *neutral, Adapter *adapter, int x = 0, int y = 0) override; 
/// Переопределяемая функция создания рыцаря
	Spear* createSpear(Map *field, Creating *neutral, Adapter *adapter, int x = 0, int y = 0) override; 
/// Переопределяемая функция создания мага
	Magician* createMagician(Map *field, Creating *neutral, Adapter *adapter, int x = 0, int y = 0) override; 
/// Переопределяемая функция создания целителя
	Healer* createHealer(Map *field, Creating *neutral, Adapter *adapter, int x = 0, int y = 0) override; 
/// Переопределяемая функция создания лучника
	Archer* createArcher(Map *field, Creating *neutral, Adapter *adapter, int x = 0, int y = 0) override;
/// Переопределяемая функция создания арбалетчика
	Arbalester* createArbalester(Map *field, Creating *neutral, Adapter *adapter, int x = 0, int y = 0) override; 
/// Функция отображения всех юнитов 
	bool showAllUnits(Adapter *adapter); 
/// Функция отображения доступного функционала базы
	void functional(Map* field, Creating *neutral, Adapter *adapter); 
/// Функция выбора юнита
	int selectUnit(Map* field, Adapter *adapter); 
/// Функция, отображающая количество ресурсов базы
	void showResour(Adapter *adapter); 
/// Функция, отображающая состояние базы в обычном режиме 
	void showState(Adapter *adapter); 
/// Функция получения особого ресурса в обычном режиме 
	int getEster(Adapter *adapter); 
/// Функция получения количества HP базы в обычном режиме 
	int getHealth(Adapter *adapter); 
/// Функция получения состояния щита в обычном режиме 
	bool getShild(Adapter *adapter); 
/// Функция получения особого ресурса в режиме загрузки сохранения
	int getEster(); 
/// Функция получения HP в режиме загрузки сохранения
	int getHealth(); 
/// Функция получения состояния щита в режиме загрузки сохранения
	bool getShild(); 
/// Функция получения базы
	Bases* getBase();
/// Функция активации щита
	void activateShild(Adapter *adapter); 
/// Функция вывода умений
	void skills(Adapter *adapter); 
/// Структура состояния войска
	struct List { 
		int count_unit[3] = { 0 , 0 , 0 };
		int count_warlock[3] = { 0 , 0 , 0 };
		int count_archer[3] = { 0 , 0 , 0 };
		int count_warrior[3] = { 0 , 0 , 0 };
	}list; 
/// Деструктор базы
	~Bases() {} 
};

