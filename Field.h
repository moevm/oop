#ifndef CELL_H
#define CELL_H

#include <cassert>
#include "objects/Unit.h"

struct Coordinates {
    int x;
    int y;
    Coordinates(int x, int y) : x(x), y(y) {}
};

class Field
{
    const int fieldHeight, fieldWidth;
    Object ***field;
    int num_units;
    const int max_num_units;
public:
    class Iterator
    {
    private:
        Object** head;
        Object*** arr;
        int height, width;
        int i, j;
    public:
        Iterator(Object**, Object*** = nullptr, int = 0, int = 0, int = 0, int = 0);
        Iterator operator++(int);
        Iterator operator++();
        Object* operator*();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
    };

    Field();
    Iterator begin();
    Iterator end();
    explicit Field(int, int, int);
    Field(const Field&);
    ~Field();
    int height() const;
    int width() const;
    bool empty() const;
    void add_unit(Object*, Coordinates);
    void del_unit(Coordinates);
    bool move(Coordinates, Moves);
    std::string get_type(int, int) const;
};

#endif // CELL_H
