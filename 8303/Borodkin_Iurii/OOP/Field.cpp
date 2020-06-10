#include "Field.h"
#include <QDebug>

bool isUnit(Object* obj)
{
    return dynamic_cast<Unit*>(obj) != nullptr;
}

bool isBase(Object* obj)
{
    return dynamic_cast<Base*>(obj) != nullptr;
}

Field::Iterator::Iterator(Object** obj, Object*** arr, size_t height,
                          size_t width, size_t i, size_t j) : head(obj),
                                                              arr(arr),
                                                              height(height),
                                                              width(width),
                                                              i(i), j(j)
{}

Field::Iterator Field::Iterator::operator++(int)
{
    if (!this->head) return Iterator(nullptr);

    for (size_t _j = j + 1; _j < width; _j++)
        if (arr[i][_j]) {
            head = arr[i] + _j;
            j = _j;
            return *this;
        }

    for (size_t _i = i + 1; _i < height; _i++)
        for (size_t _j = 0; _j < width; _j++)
            if (arr[_i][_j] != nullptr) {
                i = _i;
                j = _j;
                head = arr[_i] + _j;
                return *this;
            }

    head = nullptr;
    return *this;
}

Field::Iterator Field::Iterator::operator++()
{
    (*this)++;
    return *this;
}


Object* Field::Iterator::operator*()
{
    return arr ? *head : nullptr;
}

bool Field::Iterator::operator==(const Iterator& it) const
{
    return it.head == this->head;
}

bool Field::Iterator::operator!=(const Iterator & it) const
{
    return !(it == *this);
}

Field::Field() : fieldHeight(0), fieldWidth(0), field(nullptr),
                 numUnits(0), maxNumUnits(0), maxNumUnitsBase(0)
{}

Field::Iterator Field::begin()
{
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
            if (field[i][j])
                return Iterator(field[i] + j, field, height(), width(), i, j);

    return end();
}

Field::Iterator Field::end()
{
    return Iterator(nullptr);
}

Field::Field(int n, int m, int max_num_units, int max_num_units_base) : fieldHeight(size_t(n)), fieldWidth(size_t(m)), field(new Object**[fieldHeight]),
                                              maxNumUnits(max_num_units), maxNumUnitsBase(max_num_units_base)
{
    assert(n >= 0);
    assert(m >= 0);

    numUnits = 0;
    max_num_units = n * m;
    for (size_t i = 0; i < fieldHeight; i++)
        field[i] = new Object*[fieldWidth];

    for (size_t i = 0; i < fieldHeight; i++)
        for (size_t j = 0; j < fieldWidth; j++)
            field[i][j] = nullptr;
}

Field::Field(const Field &obj) : fieldHeight(obj.fieldHeight),
                              fieldWidth(obj.fieldWidth),
                              field(obj.empty() ? nullptr :
                                   new Object**[fieldHeight]),
                              numUnits(obj.numUnits),
                              maxNumUnits(obj.maxNumUnits),
                              maxNumUnitsBase(obj.maxNumUnitsBase)
{
    for (size_t i = 0; i < fieldHeight; i++)
        field[i] = new Object*[fieldWidth];

    for (size_t i = 0; i < fieldHeight; i++)
        for (size_t j = 0; j < fieldWidth; j++)
            field[i][j] = obj.field[i][j];
}

Field::~Field()
{
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
        {
            if (!isDeleted[field[i][j]])
                delete field[i][j];
            isDeleted[field[i][j]] = true;
        }

    for (size_t i = 0; i < fieldHeight; i++)
        delete[] field[i];

    delete[] field;
}

size_t Field::height() const
{
    return fieldHeight;
}

size_t Field::width() const
{
    return fieldWidth;
}

bool Field::empty() const
{
    return field == nullptr;
}

int Field::numUnit() const
{
    return numUnits;
}

void Field::addUnit(Unit* obj, const Coordinates &coords)
{
    if (!((coords.y < int(fieldHeight) && coords.y >= 0) &&
          (coords.x < int(fieldWidth) && coords.x >= 0)) || !obj)
        return;

    if (!field[coords.y][coords.x]) {
        if (numUnits == maxNumUnits)
            return;
        field[coords.y][coords.x] = obj;
        numUnits++;
    } else if (field[coords.y][coords.x]->type() == "Base") {
        field[coords.y][coords.x]->createUnit(obj);
    }
}

void Field::addBase(Base* obj, const Coordinates &coords)
{
    if (!((coords.y + 1 < int(fieldHeight) && coords.y >= 0) &&
          (coords.x + 1< int(fieldWidth) && coords.x >= 0)))
        return;

    if (!field[coords.y][coords.x] && !field[coords.y + 1][coords.x + 1] &&
        !field[coords.y][coords.x + 1] && !field[coords.y + 1][coords.x]) {

        field[coords.y][coords.x] = obj;
        field[coords.y + 1][coords.x] = obj;
        field[coords.y][coords.x + 1] = obj;
        field[coords.y + 1][coords.x + 1] = obj;
    }
}

void Field::delObject(const Coordinates &coords)
{
    if (!(coords.y < int(fieldHeight) && coords.y >= 0 &&
          coords.x < int(fieldWidth) && coords.x >= 0))
        return;
    numUnits -= field[coords.y][coords.x]
                 ? 1 : 0;
    delete field[coords.y][coords.x];

    field[coords.y][coords.x] = nullptr;
}

bool Field::move(const Coordinates &coords, Moves move)
{
    if (!(coords.y < int(fieldHeight) && coords.y >= 0 &&
          coords.x < int(fieldWidth) && coords.x >= 0) ||
          !field[coords.y][coords.x])
        return false;

    switch (move)
    {
        case Moves::UP:
            if (coords.y + 1 >= int(fieldHeight) || field[coords.y + 1][coords.x])
                return false;
            std::swap(field[coords.y][coords.x],
                      field[coords.y + 1][coords.x]);
            break;
        case Moves::DOWN:
            if (coords.y - 1 < 0 || field[coords.y - 1][coords.x])
                return false;
            std::swap(field[coords.y][coords.x],
                      field[coords.y - 1][coords.x]);
            break;
        case Moves::LEFT:
            if (coords.x - 1 < 0 || field[coords.y][coords.x - 1])
                return false;
            std::swap(field[coords.y][coords.x - 1],
                      field[coords.y][coords.x]);
            break;

        case Moves::RIGHT:
            if (coords.x + 1 >= int(fieldWidth) || field[coords.y][coords.x + 1])
                return false;
            std::swap(field[coords.y][coords.x + 1],
                      field[coords.y][coords.x]);
            break;
    }

    return true;
}
