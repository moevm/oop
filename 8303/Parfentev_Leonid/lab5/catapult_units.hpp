#ifndef _H_CATAPULT_UNITS_HPP
#define _H_CATAPULT_UNITS_HPP

#include <utility>
#include <random>
#include <math.h>

#include "point.hpp"
#include "unit.hpp"
#include "common_policies.hpp"
#include "ranged_units.hpp"


class CatapultAttack: public RangedAttack {
    double _spread_tang, _spread_normal;

    struct FVec2 {
        double x, y;

        explicit FVec2(const Vec2 &v)
            :x{(double)v.x()}, y{(double)v.y()} {}

        FVec2(double x, double y)
            :x{x}, y{y} {}

        operator Vec2() const
        {
            return Vec2{int(round(x)), int(round(y))};
        }

        FVec2
        orthogonal() const { return {y, -x}; }

        FVec2 &
        operator*=(double a)
        {
            x *= a;
            y *= a;
            return *this;
        }
        FVec2
        operator*(double a) const
        {
            FVec2 tmp {*this};
            return tmp *= a;
        }

        FVec2
        normalized() const { return (*this) * (1/sqrt(x*x + y*y)); }

        FVec2 &
        operator+=(const FVec2 &dxy)
        {
            x += dxy.x;
            y += dxy.y;
            return *this;
        }
        FVec2
        operator+(const FVec2 &dxy) const
        {
            FVec2 tmp{*this};
            return tmp += dxy;
        }

        FVec2
        apply(double t, double n) const
        {
            return normalized() * t
                + orthogonal().normalized() * n;
        }
    };

public:
    explicit CatapultAttack(AttackKind kind=AttackKind::invalid,
                            int base_dmg=0,
                            double min_dist=0,
                            double max_dist=0,
                            double dist_pow=0,
                            double spread_t=0,
                            double spread_n=0)
        :RangedAttack{kind, base_dmg, min_dist, max_dist, dist_pow},
         _spread_tang{spread_t},
         _spread_normal{spread_n} {}

    virtual MapIter
    actualPosition(const Unit *u, MapIter to) override
    {
        Vec2 dest = to.point();
        Vec2 delta = dest.delta(u->position());
        FVec2 fdelta {delta};

        std::uniform_real_distribution<>
            t_dist {-_spread_tang, _spread_tang},
            n_dist {-_spread_normal, _spread_normal};

        double
            t = t_dist(global_random),
            n = n_dist(global_random);

        FVec2 result = fdelta.apply(t, n);
        return to.shifted(Vec2{result});
    }

    virtual void
    store(std::ostream &os) const override
    {
        os << "ap_catapult " << static_cast<int>(_kind)
           << " " << _base_damage << " " << _min_distance
           << " " << _max_distance << " "
           << _dist_pow << " " << _spread_tang << " "
           << _spread_normal << "\n";
    }

    virtual bool
    restore(std::istream &is, RestorerTable *)
    {
        int x;
        is >> x >> _base_damage >> _min_distance
           >> _max_distance >> _dist_pow >> _spread_tang
           >> _spread_normal;
        _kind = static_cast<AttackKind>(x);
        return !is.fail();
    }
};

class BasicCatapultUnit: public Unit {
public:
    BasicCatapultUnit(AttackKind attack_kind,
                      int base_dmg,
                      double min_dist,
                      double max_dist,
                      double dist_pow,
                      double spread_t,
                      double spread_n,
                      int base_health)
        :Unit{new BasicMovement {1},
              new CatapultAttack {attack_kind,
                                  base_dmg, min_dist, max_dist,
                                  dist_pow, spread_t, spread_n},
              DefenseLevelDeco::good_defense_deco(
                  AttackKind::arrow,
                  new BasicDefense {0.75}),
              base_health} {}
};

namespace units {
    class Onager: public BasicCatapultUnit {
    public:
        Onager() :BasicCatapultUnit{
            AttackKind::rock, 90,
            3, 10, 0.05,
            0.2, 0.1,
            30} {}

        UNIT_STORABLE_NAME("u_onager");
    };

    class BoltThrower: public BasicCatapultUnit {
    public:
        BoltThrower() :BasicCatapultUnit{
            AttackKind::bolt, 110,
            2, 6, 0.15,
            0.05, 0.05,
            20} {}

        UNIT_STORABLE_NAME("u_boltthrower");
    };
}

#endif
