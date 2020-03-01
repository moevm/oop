#ifndef _UNIT_HPP_
#define _UNIT_HPP_

#include <assert.h>

#include "map.hpp"

namespace events {
    class EventLoop;
}


class BaseUnit {
    GamePos _pos {};
    int _health;

    bool place();
    void unplace();

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
    void die();

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
    baseDamage(const GamePos &) const { return {0}; }
    virtual DamageSpec
    damageMultipler(const BaseUnit *) const { return {1}; }

    virtual bool canAttack(const GamePos &) const =0;
    virtual bool canMove(const GamePos &) const =0;

    void
    putDamage(BaseUnit *from,
              DamageSpec modifier,
              events::EventLoop *el);
    virtual void
    attack(const GamePos &pos,
           events::EventLoop *el)
    {
        assert(pos.valid());
        assert(pos.cell().unit());

        pos.cell().unit()->putDamage(this, {1}, el);
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
