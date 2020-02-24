#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_

#include <random>
#include <iterator>

#include <assert.h>

class BaseUnit;

class GameCell {
    BaseUnit *_unit = nullptr;

    void destroy();
    void copy_from(const GameCell &c);
    void move_from(GameCell &&c);

public:
    GameCell() {}

    GameCell(const GameCell &c) { copy_from(c); }
    GameCell &operator=(const GameCell &c)
    {
        destroy();
        copy_from(c);
        return *this;
    }
    GameCell(GameCell &&c) { move_from(std::move(c)); }
    GameCell &operator=(GameCell &&c)
    {
        destroy();
        move_from(std::move(c));
        return *this;
    }
    ~GameCell() { destroy(); }

    BaseUnit *unit() const { return _unit; }
    void setUnit(BaseUnit *u) { _unit = u; }
};

class GameMap;

class GamePos {
    GameMap *_map;
    int _x, _y;

public:
    GamePos() :_map{nullptr} {}
    GamePos(GameMap *map, int x, int y)
        :_map{map}, _x{x}, _y{y} {}
    GamePos(const GameMap *map, int x, int y)
        :_map{const_cast<GameMap *>(map)}, _x{x}, _y{y} {}

    int x() const { return _x; }
    int y() const { return _y; }
    GameMap *map() const { return _map; }

    bool operator==(const GamePos &pos) const;
    bool operator!=(const GamePos &pos) const { return *this == pos; }

    bool null() const { return _map == nullptr; }
    operator bool() const { return !null(); }
    bool valid() const;

    void reset() { *this = GamePos{}; }

    GameCell &cell() const;

    double distance(const GamePos &pos) const
    {
        assert(_map == pos._map);
        int dx = _x - pos._x,
            dy = _y - pos._y;
        return sqrt(dx*dx + dy*dy);
    }

    bool adjacent(const GamePos &pos) const;
    bool pathExistsTo(const GamePos &pos, int max_length=-1) const;
};

template<bool const_p, typename T>
using const_mb_t = typename std::conditional<const_p, const T, T>::type;

template<bool constp>
class GameMapIter {
    GamePos _pos;

    int total() const;
    void advance(int n);

public:
    using difference_type = int;
    using value_type = GameCell;
    using pointer = const_mb_t<constp, GameCell *>;
    using reference = const_mb_t<constp, GameCell &>;
    using iterator_category = std::random_access_iterator_tag;

    const GamePos &position() const { return _pos; }

    GameMapIter(const GamePos &pos) :_pos{pos}
    {
        assert(!pos.null());
    }

    reference operator*() const
    {
        assert(_pos.valid());
        return _pos.cell();
    }
    pointer operator->() const
    {
        assert(_pos.valid());
        return &_pos.cell();
    }

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
        return _pos == i._pos;
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
    int _w, _h;
    GameCell *_map;
    int _max_units = 0, _cur_units = 0;

    void destroy();
    void copy_from(const GameMap &m);

    void throw_units_count();

public:
    GameMap() :_map{nullptr} {}
    GameMap(int w, int h)
        :_w{w}, _h{h},
         _map{new GameCell[w * h]} {}

    GameMap(const GameMap &m) { copy_from(m); }
    GameMap &operator=(const GameMap &m)
    {
        destroy();
        copy_from(m);
        return *this;
    }
    ~GameMap() { delete[] _map; }

    using iterator = GameMapIter<false>;
    using const_iterator = GameMapIter<true>;
    using reverse_iterator =
        std::reverse_iterator<iterator>;
    using const_reverse_iterator =
        std::reverse_iterator<const_iterator>;

    iterator begin() { return iterator{{this, 0, 0}}; }
    const_iterator begin() const
    {
        return const_iterator{{this, 0, 0}};
    }
    const_iterator cbegin() const { return begin(); }

    reverse_iterator rbegin() { return reverse_iterator{end()}; }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator{end()};
    }
    const_reverse_iterator crbegin() const { return rbegin(); }

    iterator end() { return iterator{{this, 0, _h}}; }
    const_iterator end() const { return const_iterator{{this, 0, _h}}; }
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
    void setMaxUnitsCount(int n);

    GameCell &operator()(int x, int y);
    const GameCell &operator()(int x, int y) const;

    bool placeUnit(BaseUnit *u);
    void removeUnit(BaseUnit *u);
};

template<bool constp>
int
GameMapIter<constp>::total() const
{
    return _pos.x() + _pos.y() * _pos.map()->width();
}

template<bool constp>
void
GameMapIter<constp>::advance(int n)
{
    int width = _pos.map()->width(),
        ttl = total() + n,
        x = ttl % width,
        y = ttl / width;
    _pos = GamePos{_pos.map(), x, y};
}

template<bool constp>
int
GameMapIter<constp>::operator-(const GameMapIter<constp> &i) const
{
    return this->total() - i.total();
}

template<bool constp>
bool
GameMapIter<constp>::operator<(const GameMapIter<constp> &i) const
{
    assert(_pos.map() == i._pos.map());
    return (_pos.y() < i._pos.y())
        || (_pos.x() < i._pos.x());
}

template<bool constp>
GameMapIter<constp>
operator+(int n, const GameMapIter<constp> &iter);

template<bool constp>
GameMapIter<constp>
operator-(int n, const GameMapIter<constp> &iter);

class BaseUnit {
    GamePos _pos {};
    int _health;
    static std::default_random_engine random;

    bool place();
    void unplace();
    void die();

public:
    explicit BaseUnit(int health) :_health{health} {}

    // mustn’t place the clone anywhere
    virtual BaseUnit *copy() const =0;

    GamePos &position() { return _pos; }
    const GamePos &position() const { return _pos; }
    bool moveTo(const GamePos &pos);

    int health() const { return _health; }
    bool alive() const { return _health > 0; }
    void takeDamage(int dmg);

    struct Damage {
        double value, spread;

        Damage(double v, double s) :value{v}, spread{s} {}
        Damage(double x) :Damage{x, x} {}

        static Damage part(double x, double part)
        {
            return {x, x * part};
        }

        Damage &operator*=(const Damage &d)
        {
            value *= d.value;
            spread *= d.spread;
            return *this;
        }
        Damage operator*(const Damage &d) const
        {
            Damage tmp = *this;
            return tmp *= d;
        }
    };
    virtual Damage
    baseDamage(const GamePos &) const { return {0}; }
    virtual Damage
    damageMultipler(const BaseUnit *) const
    {
        return {1};
    }

    static int getDamageValue(Damage damage);
    void beAttacked(const BaseUnit *by, Damage modifier={1});

    virtual bool canAttack(const GamePos &) const =0;
    virtual bool canMove(const GamePos &) const =0;

    virtual void attack(const GamePos &pos)
    {
        assert(pos.valid());
        assert(pos.cell().unit());

        pos.cell().unit()->beAttacked(this);
    };

    virtual ~BaseUnit() {}
};

class BaseUnitFactory {
public:
    virtual BaseUnit *create() const =0;
};

template<typename T>
class BasicUnitFactory : public BaseUnitFactory {
public:
    virtual BaseUnit *create() const override { return new T {}; }
};

#endif
