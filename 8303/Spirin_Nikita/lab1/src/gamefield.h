//Разработать и реализовать набор классов:
//Класс игрового поля
//Набор классов юнитов

//Игровое поле является контейнером для объектов представляющим прямоугольную сетку. Основные требования к классу игрового поля:
//Создание поля произвольного размера
//Контроль максимального количества объектов на поле
//Возможность добавления и удаления объектов на поле
//Возможность копирования поля (включая объекты на нем)
//Для хранения запрещается использовать контейнеры из stl
//Юнит является объектов, размещаемым на поля боя. Один юнит представляет собой отряд. Основные требования к классам юнитов:
//Все юниты должны иметь как минимум один общий интерфейс
//Реализованы 3 типа юнитов (например, пехота, лучники, конница)
//Реализованы 2 вида юнитов для каждого типа(например, для пехоты могут быть созданы мечники и копейщики)
//Юниты имеют характеристики, отражающие их основные атрибуты, такие как здоровье, броня, атака.
//Юнит имеет возможность перемещаться по карте


#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "unit.h"
#include <iostream>
#include <windows.h>
#include "arrofpoints.h"

class Cell
{
    friend class GameField;

    int x;
    int y;

    Unit* unit;
    char value;
};

struct DestinationPoint
{
    int x;
    int y;
};

class GameField
{
    //friend class Unit;

    Cell** field;

    DestinationPoint* point;
    ArrOfPoints* arrOfPoints;

    const int height;
    const int width;


    int numOfObj = 0;
    const int maxNumOfObj;

    void findWay(int y, int x, int length);
public:
    GameField(GameField&& f);
    GameField(GameField const& f);
    GameField(int height, int width);
    void addUnit(Unit* unit, int y, int x);
    void deleteUnit(Unit* unit);
    void printField() const;
    void deleteUnit();
    void moveUnit(Unit* unit, int y, int x);
};



#endif // GAMEFIELD_H
