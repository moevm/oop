#ifndef _H_RANGED_UNITS_HPP
#define _H_RANGED_UNITS_HPP

#include <utility>
#include <math.h>

#include "point.hpp"
#include "unit.hpp"
#include "common_policies.hpp"


class RangedAttack: public AttackPolicy {
protected:
    AttackKind _kind;
    int _base_damage;
    double _min_distance, _max_distance;
    double _dist_pow;

    static double
    distance(const Unit *u, MapIter to)
    {
        return to.point().distance(u->position());
    }

public:
    double minRange() const { return _min_distance; }
    double maxRange() const { return _max_distance; }

    explicit RangedAttack(AttackKind kind=AttackKind::invalid,
                          int base_dmg=0,
                          double min_dist=0,
                          double max_dist=0,
                          double dist_pow=0)
        :_kind{kind},
         _base_damage{base_dmg},
         _min_distance{min_dist},
         _max_distance{max_dist},
         _dist_pow{dist_pow} {}

    virtual bool
    canAttackTo(const Unit *u, MapIter to) override
    {
        double dist = distance(u, to);
        return dist >= _min_distance
            && dist <= _max_distance;
    }

    virtual std::pair<AttackKind, int>
    baseAttack(const Unit *u, MapIter to) override
    {
        double dist = distance(u, to);
        return std::make_pair(
            _kind,
            int(_base_damage
                * u->relativeHealth()
                / pow(dist, _dist_pow)));
    }

    virtual void
    store(std::ostream &os) const override
    {
        os << "ap_ranged " << static_cast<int>(_kind)
           << " " << _base_damage << " " << _min_distance
           << " " << _max_distance << " "
           << _dist_pow << "\n";
    }

    virtual bool
    restore(std::istream &is, RestorerTable *)
    {
        int x;
        is >> x >> _base_damage >> _min_distance
           >> _max_distance >> _dist_pow;
        _kind = static_cast<AttackKind>(x);
        return !is.fail();
    }
};

class BasicRangedUnit: public Unit {
public:
    BasicRangedUnit(int speed,
                    AttackKind attack_kind,
                    int base_dmg,
                    double max_dist,
                    double dist_pow,
                    DefensePolicy *def,
                    int base_health)
        :Unit{new BasicMovement {speed},
              new RangedAttack {attack_kind, base_dmg,
                                1., max_dist, dist_pow},
              def, base_health} {}
};

namespace units {
    class Archer: public BasicRangedUnit {
    public:
        Archer() :BasicRangedUnit{
            2,
            AttackKind::arrow, 50, 5., .20,
            new BasicDefense {0.9},
            40} {}

        UNIT_STORABLE_NAME("u_archer");
    };

    class Slinger: public BasicRangedUnit {
    public:
        Slinger() :BasicRangedUnit{
            2,
            AttackKind::stone, 60, 3., .30,
            new BasicDefense {.09},
            50} {}

        UNIT_STORABLE_NAME("u_slinger");
    };
}

#endif
