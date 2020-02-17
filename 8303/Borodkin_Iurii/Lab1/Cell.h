#ifndef CELL_H
#define CELL_H

#include <cassert>
#include "objects/Unit.h"


class Cell
{
    int size_n, size_m;
    Object ***cell;
    int num_units;
    int max_num_units;
public:
    Cell();
    explicit Cell(int);
    explicit Cell(int, int);
    Cell(const Cell&);
    ~Cell();
    int n() const;
    int m() const;
    bool empty() const;
    void set_max_num_units(int);
    void add_unit(Object*);
    void del_unit(std::pair<int, int>);
    bool move(std::pair<int, int>, Object::Moves, bool);
    std::string get_type(int, int);
};

#endif // CELL_H
