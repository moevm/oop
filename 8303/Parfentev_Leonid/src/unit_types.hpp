#ifndef _UNIT_TYPES_HPP_
#define _UNIT_TYPES_HPP_

#include "game.hpp"

namespace units {

    class BasicMeleeUnit : public BaseUnit {
        static constexpr double _defence_multiplier = 0.8;

    public:
        using BaseUnit::BaseUnit;

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *) const =0;

        virtual DamageSpec
        damageMultipler(const BaseUnit *attacker) const override;

        virtual void
        attack(const GamePos &pos, EventLoop *el) override;

        virtual bool
        canAttack(const GamePos &pos) const override;
    };

    class Swordsman : public BasicMeleeUnit {
        static constexpr int _base_health = 100;
        static constexpr double _base_damage = 40;
        static constexpr double _damage_spread = .10;
        static constexpr int _basic_speed = 2;

    public:
        Swordsman() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Swordsman {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual DamageSpec
        baseDamage(const GamePos &) const override
        {
            return DamageSpec::part(
                _base_damage * ((double)health()/_base_health),
                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, _basic_speed);
        }
    };

    class Spearsman : public BasicMeleeUnit {
        static constexpr int _base_health = 80;
        static constexpr double _base_damage = 35;
        static constexpr double _damage_spread = .05;
        static constexpr int _basic_speed = 2;

    public:
        Spearsman() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Spearsman {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual DamageSpec
        baseDamage(const GamePos &) const override
        {
            return DamageSpec::part(
                _base_damage * ((double)health()/_base_health),
                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, _basic_speed);
        }
    };

    class Rider : public BasicMeleeUnit {
        static constexpr int _base_health = 75;
        static constexpr double _base_damage = 50;
        static constexpr double _damage_spread = .10;
        static constexpr int _basic_speed = 3;

    public:
        Rider() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Rider {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual DamageSpec
        baseDamage(const GamePos &) const override
        {
            return DamageSpec::part(
                _base_damage * ((double)health()/_base_health),
                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, _basic_speed);
        }
    };



    class BasicRangedUnit : public BaseUnit {
    public:
        using BaseUnit::BaseUnit;

        virtual double
        shootingRange() const =0;

        virtual bool
        canAttack(const GamePos &pos) const override;
    };

    class Archer : public BasicRangedUnit {
        static constexpr int _base_health = 70;
        static constexpr double _base_damage = 45;
        static constexpr double _damage_spread = .20;
        static constexpr double _shooting_range = 3;
        static constexpr double _distance_power = .20;
        static constexpr int _basic_speed = 2;

    public:
        Archer() :BasicRangedUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Archer {}; }

        virtual double
        shootingRange() const override { return _shooting_range; }

        virtual DamageSpec
        baseDamage(const GamePos &pos) const override
        {
            return DamageSpec::part(
                (_base_damage
                 * ((double)health() / _base_health)
                 / pow(position().distance(pos),
                       _distance_power)),
                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, _basic_speed);
        }
    };

    class Slinger : public BasicRangedUnit {
        static constexpr int _base_health = 70;
        static constexpr double _base_damage = 60;
        static constexpr double _damage_spread = .25;
        static constexpr double _shooting_range = 2;
        static constexpr double _distance_power = .60;
        static constexpr int _basic_speed = 2;

    public:
        Slinger() :BasicRangedUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Slinger {}; }

        virtual double
        shootingRange() const override { return _shooting_range; }

        virtual DamageSpec
        baseDamage(const GamePos &pos) const override
        {
            return DamageSpec::part(
                (_base_damage
                 * ((double)health() / _base_health)
                 / pow(position().distance(pos),
                       _distance_power)),
                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, _basic_speed);
        }
    };



    class BasicCatapult : public BaseUnit {
    public:
        struct Delta {
            double tangential, normal;

            Delta &
            operator*=(double a)
            {
                tangential *= a;
                normal *= a;
                return *this;
            }
            Delta
            operator*(double a) const
            {
                Delta tmp {*this};
                return tmp *= a;
            }
        };

    private:
        struct DeltaXY {
            double x, y;

            DeltaXY
            orthogonal() const { return {y, -x}; }

            DeltaXY &
            operator*=(double a)
            {
                x *= a;
                y *= a;
                return *this;
            }
            DeltaXY
            operator*(double a) const
            {
                DeltaXY tmp {*this};
                return tmp *= a;
            }

            DeltaXY
            normalized() const { return (*this) * (1/sqrt(x*x + y*y)); }

            DeltaXY &
            operator+=(const DeltaXY &dxy)
            {
                x += dxy.x;
                y += dxy.y;
                return *this;
            }
            DeltaXY
            operator+(const DeltaXY &dxy) const
            {
                DeltaXY tmp{*this};
                return tmp += dxy;
            }

            DeltaXY
            apply(const Delta &delta) const
            {
                return normalized() * delta.tangential
                    + orthogonal().normalized() * delta.normal;
            }
        };

        DeltaXY
        positionDelta(const GamePos &target) const;

        static GamePos
        alterTargetPos(const GamePos &pos,
                       const DeltaXY &vec,
                       const Delta &delta);

    public:
        using BaseUnit::BaseUnit;

        virtual DamageSpec
        damageMultipler(const BaseUnit *) const override;

        virtual Delta
        getDelta(const GamePos &pos) const =0;

        virtual void
        attack(const GamePos &pos,
               EventLoop *el) override;

        struct MinMaxRange {
            double min, max;
        };
        virtual MinMaxRange
        shootingMinMaxRange() const =0;

        virtual bool
        canAttack(const GamePos &pos) const override;
    };

    class Onager : public BasicCatapult {
        static constexpr int _base_health = 20;
        static constexpr double _base_damage = 150;
        static constexpr double _damage_spread = .10;
        static constexpr double _shooting_max_range = 7;
        static constexpr double _shooting_min_range = 2;
        static constexpr int _basic_speed = 1;
        static constexpr double _base_coord_delta_t = .3;
        static constexpr double _base_coord_delta_n = .1;

    public:
        Onager() :BasicCatapult{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Onager{}; }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, _basic_speed);
        }

        virtual DamageSpec
        baseDamage(const GamePos &) const override
        {
            return DamageSpec::part(_base_damage, _damage_spread);
        }

        virtual Delta
        getDelta(const GamePos &pos) const override
        {
            double dist = position().distance(pos);
            return
                Delta{_base_coord_delta_t, _base_coord_delta_n} * dist;
        }

        virtual MinMaxRange
        shootingMinMaxRange() const
        {
            return {_shooting_min_range, _shooting_max_range};
        }

    };

    class BoltThrower : public BasicCatapult {
        static constexpr int _base_health = 20;
        static constexpr double _base_damage = 125;
        static constexpr double _damage_spread = .10;
        static constexpr double _shooting_max_range = 5;
        static constexpr double _shooting_min_range = 1;
        static constexpr int _basic_speed = 1;
        static constexpr double _base_coord_delta_t = .09;
        static constexpr double _base_coord_delta_n = .03;

    public:
        BoltThrower() :BasicCatapult{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new BoltThrower{}; }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, _basic_speed);
        }

        virtual DamageSpec
        baseDamage(const GamePos &) const override
        {
            return DamageSpec::part(_base_damage, _damage_spread);
        }

        virtual Delta
        getDelta(const GamePos &pos) const override
        {
            double dist = position().distance(pos);
            return
                Delta{_base_coord_delta_t, _base_coord_delta_n} * dist;
        }

        virtual MinMaxRange
        shootingMinMaxRange() const
        {
            return {_shooting_min_range, _shooting_max_range};
        }

    };

    // TODO: ships
    // TODO: workers

}

#endif
