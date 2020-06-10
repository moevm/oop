#ifndef CELL_H
#define CELL_H

#include <cassert>
#include "Objects/Units/Unit.h"
#include "Objects/Base.h"
#include <unordered_map>

struct Coordinates
{
    int y;
    int x;
    Coordinates(int y, int x) : y(y), x(x) {}
    Coordinates(std::pair<size_t, size_t> coords) : y(int(coords.first)), x(int(coords.second)) {}
};

bool isUnit(Object*);
bool isBase(Object*);
bool isNeutural();

class Field
{
protected:
    const size_t fieldHeight, fieldWidth;
    Object ***field;
    int numUnits;
public:

    class Iterator
    {
        Object** head;
        Object*** arr;
        const size_t height, width;
        size_t i, j;
    public:
        Iterator(Object**, Object*** = nullptr, size_t = 0, size_t = 0, size_t = 0, size_t = 0);
        Iterator operator++(int);
        Iterator operator++();
        Object* operator*();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
    };

    Iterator begin();
    Iterator end();

    Field();

    explicit Field(int, int, int, int);

    const int maxNumUnits;

    const int maxNumUnitsBase;

    std::unordered_map <Object*, bool> isDeleted;

    Field(const Field&);

    ~Field();

    size_t height() const;

    size_t width() const;

    bool empty() const;

    int numUnit() const;

    void addUnit(Unit*, const Coordinates&);

    void addBase(Base*, const Coordinates&);

    void delObject(const Coordinates&);

    bool move(const Coordinates&, Moves);
};

#endif // CELL_H
