#include "game.hpp"
#include "unit_types.hpp"

namespace units {

    BaseUnit::Damage
    BasicMeleeUnit::damageMultipler(const BaseUnit *attacker) const
    {
        auto dmg = BaseUnit::damageMultipler(attacker);

        if (const auto *a =
            dynamic_cast<const BasicMeleeUnit *>(attacker))
            dmg *= {typeDamageMultiplier(a)};

        return dmg;
    }

    bool
    BasicMeleeUnit::canAttack(const GamePos &pos) const
    {
        return pos.cell().unit()
            && position().adjacent(pos);
    }


    void
    BasicMeleeUnit::attack(const GamePos &pos)
    {
        BaseUnit *target = pos.cell().unit();
        assert(target);

        target->beAttacked(this);

        if (auto *bmu = dynamic_cast<BasicMeleeUnit *>(target))
            beAttacked(bmu, {_defence_multiplier});
    }

    double
    Swordsman::typeDamageMultiplier(const BasicMeleeUnit *unit) const
    {
        return dynamic_cast<const Rider *>(unit) ? 2.0 : 1.0;
    }

    double
    Spearsman::typeDamageMultiplier(const BasicMeleeUnit *unit) const
    {
        return dynamic_cast<const Swordsman *>(unit) ? 1.5 : 1.0;
    }

    double
    Rider::typeDamageMultiplier(const BasicMeleeUnit *unit) const
    {
        return dynamic_cast<const Spearsman *>(unit) ? 1.75 : 1.0;
    }



    bool
    BasicRangedUnit::canAttack(const GamePos &pos) const
    {
        assert(position().map() == pos.map());

        return pos.cell().unit()
            && position().distance(pos) <= shootingRange();
    }

}
