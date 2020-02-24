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

        virtual Damage
        damageMultipler(const BaseUnit *attacker) const override;

        virtual void
        attack(const GamePos &pos) override;

        virtual bool
        canAttack(const GamePos &pos) const override;
    };

    class Swordsman;
    class Spearsman;
    class Rider;

    class Swordsman : public BasicMeleeUnit {
        static constexpr int _base_health = 100;
        static constexpr double _base_damage = 40;
        static constexpr double _damage_spread = .5;

    public:
        Swordsman() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Swordsman {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual Damage
        baseDamage(const GamePos &) const override
        {
            return Damage::part(
                _base_damage * ((double)health()/_base_health),
                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, 1);
        }
    };

    class Spearsman : public BasicMeleeUnit {
        static constexpr int _base_health = 80;
        static constexpr double _base_damage = 35;
        static constexpr double _damage_spread = .5;

    public:
        Spearsman() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Spearsman {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual Damage
        baseDamage(const GamePos &) const override
        {
            return Damage::part(
                _base_damage * ((double)health()/_base_health),
                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, 1);
        }
    };

    class Rider : public BasicMeleeUnit {
        static constexpr int _base_health = 75;
        static constexpr double _base_damage = 50;
        static constexpr double _damage_spread = .5;

    public:
        Rider() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Rider {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual Damage
        baseDamage(const GamePos &) const override
        {
            return Damage::part(
                _base_damage * ((double)health()/_base_health),
                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, 2);
        }
    };



    // TODO: decide on balance: dM<1 for Melee except vuln or dM>1 here?
    // TODO: also decide on the HP scale (consider rounding problems)

    class BasicRangedUnit : public BaseUnit {
    public:
        using BaseUnit::BaseUnit;

        virtual double
        shootingRange() const =0;

        virtual bool
        canAttack(const GamePos &pos) const override;
    };

    class Archer : public BasicRangedUnit {
        static constexpr int _base_health = 55;
        static constexpr double _base_damage = 55;
        static constexpr double _damage_spread = .65;
        static constexpr double _shooting_range = 3;
        static constexpr double _distance_power = .75;

    public:
        Archer() :BasicRangedUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Archer {}; }

        virtual double
        shootingRange() const override { return _shooting_range; }

        virtual Damage
        baseDamage(const GamePos &pos) const override
        {
            return Damage::part((_base_damage
                                 * ((double)health() / _base_health)
                                 / pow(position().distance(pos),
                                       _distance_power)),
                                _damage_spread);
        }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, 1);
        }
    };

    // TODO: ships
    // TODO: catapults
    // TODO: workers

}

#endif
