#ifndef _UNIT_TYPES_HPP_
#define _UNIT_TYPES_HPP_

#include "map.hpp"
#include "unit.hpp"


namespace units {

    class BasicMeleeUnit : public BaseUnit {
        static constexpr double _defence_multiplier = 0.8;

    public:
        using BaseUnit::BaseUnit;

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *) const =0;

        virtual DamageSpec
        damageMultipler(MapConstIter iter) const override;

        virtual void
        attack(MapIter iter, events::EventLoop *el) override;

        virtual bool
        canAttack(MapConstIter iter) const override;
    };

    template<typename C, typename T>
    class TemplateMeleeUnit : public BasicMeleeUnit {
    public:
        TemplateMeleeUnit() :BasicMeleeUnit{C::baseHealth} {}
        virtual BaseUnit *
        copy() const override { return new T {}; }

        virtual DamageSpec
        baseDamage(MapConstIter) const override
        {
            return DamageSpec::part(
                C::baseDamage * ((double)health()/C::baseHealth),
                C::damageSpread);
        }

        virtual bool
        canMove(MapConstIter iter) const override
        {
            return iter.map()->pathExists(point(),
                                          iter.point(),
                                          C::basicSpeed);
        }
    };

    struct SwordsmanConfig {
        static constexpr int baseHealth = 100;
        static constexpr double baseDamage = 40;
        static constexpr double damageSpread = .10;
        static constexpr int basicSpeed = 2;
    };

    class Swordsman :
        public TemplateMeleeUnit<SwordsmanConfig, Swordsman> {
    public:
        using TemplateMeleeUnit<SwordsmanConfig,
                                Swordsman>::TemplateMeleeUnit;
        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
    };

    struct SpearsmanConfig {
        static constexpr int baseHealth = 80;
        static constexpr double baseDamage = 35;
        static constexpr double damageSpread = .05;
        static constexpr int basicSpeed = 2;
    };

    class Spearsman :
        public TemplateMeleeUnit<SpearsmanConfig, Spearsman> {
    public:
        using TemplateMeleeUnit<SpearsmanConfig,
                                Spearsman>::TemplateMeleeUnit;
        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
    };

    struct RiderConfig {
        static constexpr int baseHealth = 75;
        static constexpr double baseDamage = 50;
        static constexpr double damageSpread = .10;
        static constexpr int basicSpeed = 3;
    };

    class Rider :
        public TemplateMeleeUnit<RiderConfig, Rider> {
    public:
        using TemplateMeleeUnit<RiderConfig,
                                Rider>::TemplateMeleeUnit;
        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
    };



    class BasicRangedUnit : public BaseUnit {
    public:
        using BaseUnit::BaseUnit;

        virtual double
        shootingRange() const =0;

        virtual bool
        canAttack(MapConstIter iter) const override;
    };

    template<typename C, typename T>
    class TemplateRangedUnit : public BasicRangedUnit {
    public:
        TemplateRangedUnit() :BasicRangedUnit{C::baseHealth} {}
        virtual BaseUnit *
        copy() const override { return new T {}; }

        virtual double
        shootingRange() const override { return C::shootingRange; }

        virtual DamageSpec
        baseDamage(MapConstIter iter) const override
        {
            return DamageSpec::part(
                (C::baseDamage
                 * ((double)health() / C::baseHealth)
                 / pow(point().distance(iter.point()),
                       C::distancePower)),
                C::damageSpread);
        }

        virtual bool
        canMove(MapConstIter iter) const override
        {
            return iter.map()->pathExists(point(),
                                          iter.point(),
                                          C::basicSpeed);
        }
    };

    struct ArcherConfig {
        static constexpr int baseHealth = 70;
        static constexpr double baseDamage = 45;
        static constexpr double damageSpread = .20;
        static constexpr double shootingRange = 3;
        static constexpr double distancePower = .20;
        static constexpr int basicSpeed = 2;
    };

    struct Archer : public TemplateRangedUnit<ArcherConfig, Archer> {
        using TemplateRangedUnit<ArcherConfig,
                                 Archer>::TemplateRangedUnit;
    };

    struct SlingerConfig {
        static constexpr int baseHealth = 70;
        static constexpr double baseDamage = 60;
        static constexpr double damageSpread = .25;
        static constexpr double shootingRange = 2;
        static constexpr double distancePower = .60;
        static constexpr int basicSpeed = 2;
    };

    struct Slinger : public TemplateRangedUnit<SlingerConfig, Slinger> {
        using TemplateRangedUnit<SlingerConfig,
                                 Slinger>::TemplateRangedUnit;
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
        pointDelta(const Point &target) const;

        static MapConstIter
        alterTargetPos(MapConstIter iter,
                       const DeltaXY &vec,
                       const Delta &delta);

    public:
        using BaseUnit::BaseUnit;

        virtual DamageSpec
        damageMultipler(MapConstIter iter) const override;

        virtual Delta
        getDelta(MapConstIter iter) const =0;

        virtual void
        attack(MapIter iter,
               events::EventLoop *el) override;

        struct MinMaxRange {
            double min, max;
        };
        virtual MinMaxRange
        shootingMinMaxRange() const =0;

        virtual bool
        canAttack(MapConstIter iter) const override;
    };

    template<typename C, typename T>
    class TemplateCatapult : public BasicCatapult {
    public:
        TemplateCatapult() :BasicCatapult{C::baseHealth} {}
        virtual BaseUnit *
        copy() const override { return new T {}; }

        virtual bool
        canMove(MapConstIter iter) const override
        {
            return iter.map()->pathExists(point(),
                                          iter.point(),
                                          C::basicSpeed);
        }

        virtual DamageSpec
        baseDamage(MapConstIter) const override
        {
            return DamageSpec::part(C::baseDamage, C::damageSpread);
        }

        virtual Delta
        getDelta(MapConstIter iter) const override
        {
            double dist = point().distance(iter.point());
            return
                Delta{C::baseCoordDeltaT, C::baseCoordDeltaN} * dist;
        }

        virtual MinMaxRange
        shootingMinMaxRange() const
        {
            return {C::shootingMinRange, C::shootingMaxRange};
        }

    };

    struct OnagerConfig {
        static constexpr int baseHealth = 20;
        static constexpr double baseDamage = 150;
        static constexpr double damageSpread = .10;
        static constexpr double shootingMaxRange = 7;
        static constexpr double shootingMinRange = 2;
        static constexpr int basicSpeed = 1;
        static constexpr double baseCoordDeltaT = .3;
        static constexpr double baseCoordDeltaN = .1;
    };

    struct Onager : public TemplateCatapult<OnagerConfig, Onager> {
        using TemplateCatapult<OnagerConfig, Onager>::TemplateCatapult;
    };

    struct BoltThrowerConfig {
        static constexpr int baseHealth = 20;
        static constexpr double baseDamage = 125;
        static constexpr double damageSpread = .10;
        static constexpr double shootingMaxRange = 5;
        static constexpr double shootingMinRange = 1;
        static constexpr int basicSpeed = 1;
        static constexpr double baseCoordDeltaT = .09;
        static constexpr double baseCoordDeltaN = .03;
    };

    struct BoltThrower :
        public TemplateCatapult<BoltThrowerConfig, BoltThrower> {
        using TemplateCatapult<BoltThrowerConfig,
                               BoltThrower>::TemplateCatapult;
    };

    // TODO: ships
    // TODO: workers

}

#endif
