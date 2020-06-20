#ifndef _UNIT_HPP_
#define _UNIT_HPP_

#include <assert.h>

#include "map.hpp"

namespace events {
    class EventLoop;
}


class BaseUnit {
    Point _pt {-1, -1};
    int _health;

public:
    explicit BaseUnit(int health) :_health{health} {}

    // The point of the clone must be unset (as it is by default)
    virtual BaseUnit *copy() const =0;

    bool pointSet() const { return _pt.x() >= 0 && _pt.y() >= 0; }
    Point point() const { assert(pointSet()); return _pt; }
    void setPoint(const Point &pt) { _pt = pt; }
    void unsetPoint() { _pt = Point{-1, -1}; }

    int health() const { return _health; }
    bool alive() const { return _health > 0; }
    void takeDamage(int dmg);

    struct DamageSpec {
        double value, spread;

        DamageSpec(double v, double s) :value{v}, spread{s} {}
        DamageSpec(double x) :DamageSpec{x, x} {}

        static DamageSpec part(double x, double part)
        {
            return {x, x * part};
        }

        int evaluate() const;

        DamageSpec &operator*=(const DamageSpec &d)
        {
            value *= d.value;
            spread *= d.spread;
            return *this;
        }
        DamageSpec operator*(const DamageSpec &d) const
        {
            DamageSpec tmp = *this;
            return tmp *= d;
        }
    };
    virtual DamageSpec
    baseDamage(MapConstIter) const { return {0}; }
    virtual DamageSpec
    damageMultipler(MapConstIter) const { return {1}; }

    virtual bool canAttack(MapConstIter) const =0;
    virtual bool canMove(MapConstIter) const =0;

    void
    putDamage(MapIter from,
              DamageSpec modifier,
              events::EventLoop *el);
    virtual void
    attack(MapIter iter,
           events::EventLoop *el)
    {
        iter->unit()->putDamage(iter.otherAt(point()), {1}, el);
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
