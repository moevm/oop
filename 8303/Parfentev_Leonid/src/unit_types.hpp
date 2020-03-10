#ifndef _UNIT_TYPES_HPP_
#define _UNIT_TYPES_HPP_

#include "map.hpp"
#include "unit.hpp"


namespace units {

    class BasicMeleeUnit : public BaseUnit {
    public:
        struct Config {
            int baseHealth;
            double baseDamage;
            double damageSpread;
            int basicSpeed;
        };

    private:
        const Config *_c;
        static constexpr double _defence_multiplier = 0.8;

    public:
        BasicMeleeUnit(const Config *cfg)
            :BaseUnit{cfg->baseHealth}, _c{cfg} {}

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *) const =0;

        virtual DamageSpec
        damageMultipler(MapConstIter iter) const override;

        virtual void
        attack(MapIter iter, events::EventLoop *el) override;

        virtual bool
        canAttack(MapConstIter iter) const override;

        virtual DamageSpec
        baseDamage(MapConstIter) const override
        {
            return DamageSpec::part(
                _c->baseDamage * ((double)health()/_c->baseHealth),
                _c->damageSpread);
        }

        virtual bool
        canMove(MapConstIter iter) const override
        {
            return iter.map()->pathExists(point(),
                                          iter.point(),
                                          _c->basicSpeed);
        }
    };

    class Swordsman : public BasicMeleeUnit {
        static const BasicMeleeUnit::Config _cfg;

    public:
        Swordsman() :BasicMeleeUnit{&_cfg} {}

        virtual BaseUnit *
        copy() const override { return new Swordsman {*this}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
    };

    class Spearsman : public BasicMeleeUnit {
        static const BasicMeleeUnit::Config _cfg;

    public:
        Spearsman() :BasicMeleeUnit{&_cfg} {}

        virtual BaseUnit *
        copy() const override { return new Spearsman {*this}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
    };

    class Rider : public BasicMeleeUnit {
        static const BasicMeleeUnit::Config _cfg;

    public:
        Rider() :BasicMeleeUnit{&_cfg} {}

        virtual BaseUnit *
        copy() const override { return new Rider {*this}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
    };



    class BasicRangedUnit : public BaseUnit {
    public:
        struct Config {
            int baseHealth;
            double baseDamage;
            double damageSpread;
            double shootingRange;
            double distancePower;
            int basicSpeed;
        };

    private:
        const Config *_c;

    public:
        BasicRangedUnit(const Config *cfg)
            :BaseUnit{cfg->baseHealth}, _c{cfg} {}

        virtual bool
        canAttack(MapConstIter iter) const override;

        virtual double
        shootingRange() const { return _c->shootingRange; }

        virtual DamageSpec
        baseDamage(MapConstIter iter) const override
        {
            return DamageSpec::part(
                (_c->baseDamage
                 * ((double)health() / _c->baseHealth)
                 / pow(point().distance(iter.point()),
                       _c->distancePower)),
                _c->damageSpread);
        }

        virtual bool
        canMove(MapConstIter iter) const override
        {
            return iter.map()->pathExists(point(),
                                          iter.point(),
                                          _c->basicSpeed);
        }
    };

    struct Archer : public BasicRangedUnit {
        static const BasicRangedUnit::Config _cfg;

        Archer() :BasicRangedUnit{&_cfg} {}

        virtual BaseUnit *
        copy() const override { return new Archer {*this}; }
    };

    struct Slinger : public BasicRangedUnit {
        static const BasicRangedUnit::Config _cfg;

        Slinger() :BasicRangedUnit{&_cfg} {}

        virtual BaseUnit *
        copy() const override { return new Slinger {*this}; }
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

        struct MinMaxRange {
            double min, max;
        };

        struct Config {
            int baseHealth;
            double baseDamage;
            double damageSpread;
            MinMaxRange shootingRange;
            int basicSpeed;
            Delta baseCoordDelta;
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
        pointDelta(const Point &target) const;

        static MapConstIter
        alterTargetPos(MapConstIter iter,
                       const DeltaXY &vec,
                       const Delta &delta);

    private:
        const Config *_c;

    public:
        BasicCatapult(const Config *cfg)
            :BaseUnit{cfg->baseHealth}, _c{cfg} {}

        virtual DamageSpec
        damageMultipler(MapConstIter iter) const override;

        virtual void
        attack(MapIter iter,
               events::EventLoop *el) override;

        virtual bool
        canAttack(MapConstIter iter) const override;

        virtual bool
        canMove(MapConstIter iter) const override
        {
            return iter.map()->pathExists(point(),
                                          iter.point(),
                                          _c->basicSpeed);
        }

        virtual DamageSpec
        baseDamage(MapConstIter) const override
        {
            return DamageSpec::part(_c->baseDamage, _c->damageSpread);
        }

        Delta
        getDelta(MapConstIter iter) const
        {
            double dist = point().distance(iter.point());
            return _c->baseCoordDelta * dist;
        }
    };

    struct Onager : public BasicCatapult {
        static const BasicCatapult::Config _cfg;

    public:
        Onager() :BasicCatapult{&_cfg} {}

        virtual BaseUnit *
        copy() const override { return new Onager {*this}; }
    };

    struct BoltThrower : public BasicCatapult {
        static const BasicCatapult::Config _cfg;

    public:
        BoltThrower() :BasicCatapult{&_cfg} {}

        virtual BaseUnit *
        copy() const override { return new BoltThrower {*this}; }
    };

    // TODO: ships
    // TODO: workers

}

#endif
