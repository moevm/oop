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
        attack(const GamePos &) override;

        virtual bool
        canAttack(const GamePos &pos) const override
        {
            return position().adjacent(pos)
                && pos.cell().unit();
        }
    };

    class Swordsman;
    class Spearsman;
    class Rider;

    class Swordsman : public BasicMeleeUnit {
        static constexpr int _base_health = 10;
        static constexpr double _base_damage = 3;

    public:
        Swordsman() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Swordsman {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual Damage
        baseDamage() const override { return {_base_damage}; }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, 1);
        }
    };

    class Spearsman : public BasicMeleeUnit {
        static constexpr int _base_health = 8;
        static constexpr double _base_damage = 3.5;

    public:
        Spearsman() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Spearsman {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual Damage
        baseDamage() const override { return {_base_damage}; }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, 1);
        }
    };

    class Rider : public BasicMeleeUnit {
        static constexpr int _base_health = 8;
        static constexpr double _base_damage = 4;

    public:
        Rider() :BasicMeleeUnit{_base_health} {}
        virtual BaseUnit *
        copy() const override { return new Rider {}; }

        virtual double
        typeDamageMultiplier(const BasicMeleeUnit *unit) const override;
        virtual Damage
        baseDamage() const override { return {_base_damage}; }

        virtual bool
        canMove(const GamePos &pos) const override
        {
            return position().pathExistsTo(pos, 2);
        }
    };

    // TODO: ships
    // TODO: catapults
    // TODO: workers

}

#endif
