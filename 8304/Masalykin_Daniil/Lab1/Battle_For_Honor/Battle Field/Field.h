#ifndef BATTLE_FOR_HONOR_FIELD_H
#define BATTLE_FOR_HONOR_FIELD_H

#include <iostream>
#include "Cell.h"

#define X 15
#define Y 10
#define SIZE 20

class Field
{
    int object_count;
    const int limit = SIZE;

public:
    Cell** field = nullptr;
    const int lengthX;
    const int lengthY;
    Field() : lengthY(Y), lengthX(X)
    {
        object_count = 0;
        field = new Cell * [lengthY];
        for (int i = 0; i < lengthY; i++)
        {
            field[i] = new Cell  [lengthX];

        }
    }

    ~Field()
    {
        for (int i = 0; i < lengthY; i++)
        {
            delete[] field[i];
        }
        delete[] field;
    }
    bool move_unit(Unit*, int, int);

    bool check_max_count()
    {
        return (object_count <= limit);
    }

    void insert_Unit(Unit* obj)
    {
        if (object_count <= limit &&check_max_count() && obj->getX() < this->lengthX && obj->getY() < this->lengthY && field[obj->getY()][obj->getX()].is_full == false)
        {
            field[obj->getY()][obj->getX()].unit = obj;
            field[obj->getY()][obj->getX()].is_full = true;
            object_count++;
        }
    }

    void remove_Unit(Unit* obj)
    {
        if (obj != nullptr)
        {
            Cell new_cell;
            field[obj->getY()][obj->getX()] = new_cell;
            object_count--;
        }
    }

    void print_field() const
    {
        for (int i = 0; i < this->lengthY; i++)
        {
            for (int j = 0; j < this->lengthX; j++)
            {
                if (field[i][j].is_full == false)
                {
                    std::cout << 0 << ' ';
                }
                else
                {
                    std::cout << field[i][j].unit->getSymbol() << ' ';
                }
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
};

#endif //BATTLE_FOR_HONOR_FIELD_H
