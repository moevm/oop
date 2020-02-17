#include "Cell.h"

Cell::Cell() : size_n(0), size_m(0), cell(nullptr),
               num_units(0), max_num_units(0)
{}

Cell::Cell(int n) : size_n(n), size_m(n), cell(new Object**[size_n])
{
    assert(n >= 0);

    num_units = 0;
    max_num_units = n * n;
    for (int i = 0; i < size_n; i++)
        cell[i] = new Object*[size_m];

    for (int i = 0; i < size_n; i++)
        for (int j = 0; j < size_m; j++)
            cell[i][j] = nullptr;
}

Cell::Cell(int n, int m) : size_n(n), size_m(m), cell(new Object**[size_n])
{
    assert(n >= 0);
    assert(m >= 0);

    num_units = 0;
    max_num_units = n * m;
    for (int i = 0; i < size_n; i++)
        cell[i] = new Object*[size_m];

    for (int i = 0; i < size_n; i++)
        for (int j = 0; j < size_m; j++)
            cell[i][j] = nullptr;
}

Cell::Cell(const Cell &obj) : size_n(obj.size_n),
                              size_m(obj.size_m),
                              cell(obj.empty() ? nullptr :
                                   new Object**[size_n]),
                              num_units(obj.num_units),
                              max_num_units(obj.max_num_units)
{
    for (int i = 0; i < size_n; i++)
        cell[i] = new Object*[size_m];

    for (int i = 0; i < size_n; i++)
        for (int j = 0; j < size_m; j++)
            cell[i][j] = obj.cell[i][j];
}

Cell::~Cell()
{
    for (int i = 0; i < size_n; i++)
        delete[] cell[i];
    delete[] cell;
}

int Cell::n() const
{
    return size_n;
}

int Cell::m() const
{
    return size_m;
}

bool Cell::empty() const
{
    return cell == nullptr;
}

void Cell::set_max_num_units(int num)
{
    assert(num >= 0);
    max_num_units = num > size_m * size_n ?
                    size_m * size_n : num;
}

void Cell::add_unit(Object* obj)
{
    auto coords = obj->coordinates();
    assert(coords.second <= size_n && coords.second > 0);
    assert(coords.first <= size_m && coords.first > 0);

    if (!cell[size_n - coords.second][coords.first - 1]) {
        cell[size_n - coords.second][coords.first - 1] = obj;
        num_units++;
    }
}

void Cell::del_unit(std::pair<int, int> coords)
{
    assert(coords.second <= size_n && coords.second > 0);
    assert(coords.first <= size_m && coords.first > 0);
    num_units -= cell[size_n - coords.second][coords.first - 1]
                 ? 1 : 0;
    delete cell[size_n - coords.second][coords.first - 1];
    cell[size_n - coords.second][coords.first - 1] = nullptr;
}

bool Cell::move(std::pair<int, int> coords, Object::Moves move, bool X)
{
    if (!cell[size_n - coords.second][coords.first - 1])
        return false;

    if (X) {
        if (!(coords.first + move <= size_m && coords.first + move > 0)) return false;
        if (cell[size_n - coords.second][coords.first - 1 + move] == nullptr) {
            cell[size_n - coords.second][coords.first - 1]->moveX(move);
            std::swap(cell[size_n - coords.second][coords.first - 1],
                      cell[size_n - coords.second][coords.first - 1 + move]);
        } else return false;

    } else {
        if (!(coords.second + move <= size_n && coords.second + move > 0)) return false;
        if (cell[size_n - (coords.second + move)][coords.first - 1] == nullptr) {
            cell[size_n - coords.second][coords.first - 1]->moveY(move);
            std::swap(cell[size_n - coords.second][coords.first - 1],
                      cell[size_n - (coords.second + move)][coords.first - 1]);
        } else return false;
    }

    return true;
}

std::string Cell::get_type(int y, int x)
{
    assert(y <= size_n && y > 0);
    assert(x <= size_m && x > 0);
    return cell[y - 1][x - 1] ? cell[y-1][x-1]->type():"Object";
}
