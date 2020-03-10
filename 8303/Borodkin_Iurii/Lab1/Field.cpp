#include "Field.h"
#include <QDebug>

Field::Iterator::Iterator(Object** obj, Object*** arr, int height,
                          int width, int i, int j) : head(obj),
                                                     arr(arr),
                                                     height(height),
                                                     width(width),
                                                     i(i), j(j)
{}

Field::Iterator Field::Iterator::operator++(int)
{
    if (!this->head) return Iterator(nullptr);

    for (int _j = j + 1; _j < width; _j++)
        if (arr[i][_j]) {
            head = arr[i] + _j;
            j = _j;
            return *this;
        }

    for (int _i = i + 1; _i < height; _i++)
        for (int _j = 0; _j < width; _j++)
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
                 num_units(0), max_num_units(0)
{}

Field::Iterator Field::begin()
{
    for (int i = 0; i < height(); i++)
        for (int j = 0; j < width(); j++)
            if (field[i][j])
                return Iterator(field[i] + j, field, height(), width(), i, j);

    return end();
}

Field::Iterator Field::end()
{
    return Iterator(nullptr);
}

Field::Field(int n, int m, int max_num_units) : fieldHeight(n), fieldWidth(m), field(new Object**[fieldHeight]),
                                              max_num_units(max_num_units)
{
    assert(n >= 0);
    assert(m >= 0);

    num_units = 0;
    max_num_units = n * m;
    for (int i = 0; i < fieldHeight; i++)
        field[i] = new Object*[fieldWidth];

    for (int i = 0; i < fieldHeight; i++)
        for (int j = 0; j < fieldWidth; j++)
            field[i][j] = nullptr;
}

Field::Field(const Field &obj) : fieldHeight(obj.fieldHeight),
                              fieldWidth(obj.fieldWidth),
                              field(obj.empty() ? nullptr :
                                   new Object**[fieldHeight]),
                              num_units(obj.num_units),
                              max_num_units(obj.max_num_units)
{
    for (int i = 0; i < fieldHeight; i++)
        field[i] = new Object*[fieldWidth];

    for (int i = 0; i < fieldHeight; i++)
        for (int j = 0; j < fieldWidth; j++)
            field[i][j] = obj.field[i][j];
}

Field::~Field()
{
    for (int i = 0; i < fieldHeight; i++)
        delete[] field[i];
    delete[] field;
}

int Field::height() const
{
    return fieldHeight;
}

int Field::width() const
{
    return fieldWidth;
}

bool Field::empty() const
{
    return field == nullptr;
}

void Field::add_unit(Object* obj, Coordinates coords)
{
    if (!((coords.y < fieldHeight && coords.y >= 0) &&
          (coords.x < fieldWidth && coords.x >= 0)))
        return;

    if (!field[coords.y][coords.x]) {
        if (num_units == max_num_units)
            return;
        field[coords.y][coords.x] = obj;
        num_units++;
    }
}

void Field::del_unit(Coordinates coords)
{
    if (!((coords.y < fieldHeight && coords.y >= 0) &&
         (coords.x < fieldWidth && coords.x >= 0)))
        return;
    num_units -= field[coords.y][coords.x]
                 ? 1 : 0;
    delete field[coords.y][coords.x];
    field[coords.y][coords.x] = nullptr;
}

bool Field::move(Coordinates coords, Moves move)
{
    if (!((coords.y < fieldHeight && coords.y >= 0) &&
          (coords.x < fieldWidth && coords.x >= 0))  ||
          (!field[coords.y][coords.x]))
        return false;

    switch (move)
    {
        case Moves::UP:
            if (coords.y + 1 >= fieldHeight || field[coords.y + 1][coords.x])
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
            if (coords.x + 1 >= fieldWidth || field[coords.y][coords.x + 1])
                return false;
            std::swap(field[coords.y][coords.x + 1],
                      field[coords.y][coords.x]);
            break;
    }

    return true;
}

std::string Field::get_type(int y, int x) const
{
    if (!((y < fieldHeight && y >= 0) && (x < fieldWidth  && x >= 0))) return "Object";
    return field[y][x] ? field[y][x]->type() : "Object";
}
