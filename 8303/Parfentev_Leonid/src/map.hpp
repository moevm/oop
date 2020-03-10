#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <vector>

#include <random>
#include <iterator>

#include <assert.h>

class BaseUnit;


extern std::default_random_engine global_random;

class GameCell {
    BaseUnit *_unit = nullptr;

public:
    GameCell() {}

    GameCell(const GameCell &) =delete;
    GameCell &operator=(const GameCell &) =delete;
    GameCell(GameCell &&) =delete;
    GameCell &operator=(GameCell &&) =delete;

    ~GameCell();

    BaseUnit *unit() const { return _unit; }
    void setUnit(BaseUnit *u) { _unit = u; }
};

class GameMap;

class Point {
    int _x, _y;

public:
    Point(int x, int y) :_x{x}, _y{y} {}

    int x() const { return _x; }
    int y() const { return _y; }

    bool operator==(const Point &pt) const;
    bool operator!=(const Point &pt) const
    {
        return !(*this == pt);
    }

    double distance(const Point &pt) const;
    bool adjacent(const Point &pt) const;

    Point shifted(int dx, int dy) const { return {_x + dx, _y + dy}; }
};

template<bool constp>
class GameMapIter {
    using map_ptr_t = typename std::conditional<constp,
                                                const GameMap *,
                                                GameMap *>::type;
    using cell_t = typename std::conditional<constp,
                                             const GameCell,
                                             GameCell>::type;

    map_ptr_t _map;
    Point _pt;

    int current_index() const;
    void advance(int n);

public:
    friend class GameMapIter<!constp>;

    using difference_type = int;
    using value_type = GameCell;
    using pointer = cell_t *;
    using reference = cell_t &;
    using iterator_category = std::random_access_iterator_tag;

    GameMapIter(map_ptr_t map,
                const Point &pt)
        :_map{map}, _pt{pt} {}
    GameMapIter(map_ptr_t map,
                int x, int y)
        :GameMapIter<constp>{map, Point{x, y}} {}

    template<bool other_constp>
    GameMapIter(const GameMapIter<other_constp> &i)
        // const -> non-const won’t compile
        :_map{i._map}, _pt{i._pt} {}

    bool valid() const;

    Point point() const { return _pt; }
    map_ptr_t map() const { return _map; }

    GameMapIter<constp> otherAt(const Point &pt) const
    {
        return {_map, pt};
    }

    reference operator*() const;
    pointer operator->() const;

    GameMapIter &operator+=(int n) { advance(n); return *this; }
    GameMapIter &operator-=(int n) { return *this += -n; }
    int operator-(const GameMapIter &i) const;

    GameMapIter operator+(int n) const
    {
        GameMapIter tmp = *this;
        return tmp += n;
    }
    GameMapIter operator-(int n) const { return *this + -n; }

    GameMapIter &operator++() { return *this += 1; }
    GameMapIter operator++(int)
    {
        GameMapIter tmp = *this;
        ++*this;
        return tmp;
    }

    GameMapIter &operator--() { return *this -= 1; }
    GameMapIter operator--(int)
    {
        GameMapIter tmp = *this;
        --*this;
        return tmp;
    }

    bool operator==(const GameMapIter &i) const
    {
        return _map == i._map
            && _pt == i._pt;
    }
    bool operator!=(const GameMapIter &i) const
    {
        return !(*this == i);
    }

    bool operator<(const GameMapIter &i) const;
    bool operator<=(const GameMapIter &i) const
    {
        return *this == i || *this < i;
    }
    bool operator>=(const GameMapIter &i) const
    {
        return !(*this < i);
    }
    bool operator>(const GameMapIter &i) const
    {
        return !(*this <= i);
    }

    reference operator[](int n) const { return *(*this + n); }
};

class GameMap {
    const int _w, _h;
    GameCell * const _map;
    int _max_units = 0, _cur_units = 0;

    void destroy();

public:
    GameMap(int w, int h)
        :_w{w}, _h{h},
         _map{new GameCell[w * h]} {}

    GameMap(const GameMap &) =delete;
    GameMap &operator=(const GameMap &) =delete;
    GameMap(GameMap &&) =delete;
    GameMap &operator=(GameMap &) =delete;

    ~GameMap() { delete[] _map; }

    using iterator = GameMapIter<false>;
    using const_iterator = GameMapIter<true>;
    using reverse_iterator =
        std::reverse_iterator<iterator>;
    using const_reverse_iterator =
        std::reverse_iterator<const_iterator>;

    iterator begin() { return iterator{this, 0, 0}; }
    const_iterator begin() const
    {
        return const_iterator{this, 0, 0};
    }
    const_iterator cbegin() const { return begin(); }

    reverse_iterator rbegin() { return reverse_iterator{end()}; }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator{end()};
    }
    const_reverse_iterator crbegin() const { return rbegin(); }

    iterator end() { return iterator{this, 0, _h}; }
    const_iterator end() const { return const_iterator{this, 0, _h}; }
    const_iterator cend() const { return end(); }

    reverse_iterator rend() { return reverse_iterator{begin()}; }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator{begin()};
    }
    const_reverse_iterator crend() const { return rend(); }

    int width() const { return _w; }
    int height() const { return _h; }

    int unitsCount() const { return _cur_units; }
    int maxUnitsCount() const { return _max_units; }
    bool setMaxUnitsCount(int n);

    iterator iterAt(const Point &pt);
    const_iterator iterAt(const Point &pt) const;

    int area() const { return _w * _h; }
    int cellIndex(const Point &pt) const;

    GameCell &at(const Point &pt);
    const GameCell &at(const Point &pt) const;
    bool ptValid(const Point &pt) const;

    bool placeUnit(const Point &pt,
                   BaseUnit *u);
    BaseUnit *removeFrom(const Point &pt);

    bool pathExists(const Point &src,
                    const Point &dest,
                    int max_length=-1) const;
};

using MapIter = GameMap::iterator;
using MapConstIter = GameMap::const_iterator;

template<bool constp>
int
GameMapIter<constp>::current_index() const
{
    return _map->cellIndex(_pt);
}

template<bool constp>
void
GameMapIter<constp>::advance(int n)
{
    int width = _map->width(),
        next = current_index() + n,
        x = next % width,
        y = next / width;
    _pt = Point{x, y};
}


template<bool constp>
auto
GameMapIter<constp>::operator*() const -> reference
{
    return _map->at(_pt);
}

template<bool constp>
auto
GameMapIter<constp>::operator->() const -> pointer
{
    return &_map->at(_pt);
}

template<bool constp>
bool
GameMapIter<constp>::valid() const
{
    return _map->ptValid(_pt);
}

template<bool constp>
int
GameMapIter<constp>::operator-(const GameMapIter<constp> &i) const
{
    return this->current_index() - i.current_index();
}

template<bool constp>
bool
GameMapIter<constp>::operator<(const GameMapIter<constp> &i) const
{
    assert(_map == i._map);
    return (_pt.y() < i._pt.y())
        || (_pt.x() < i._pt.x());
}

template<bool constp>
GameMapIter<constp>
operator+(int n, const GameMapIter<constp> &iter);

template<bool constp>
GameMapIter<constp>
operator-(int n, const GameMapIter<constp> &iter);


#endif
