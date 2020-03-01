#include "map.hpp"
#include "unit.hpp"
#include "event.hpp"
#include "unit_types.hpp"


namespace units {

    BaseUnit::DamageSpec
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
    BasicMeleeUnit::attack(const GamePos &pos, events::EventLoop *el)
    {
        BaseUnit *target = pos.cell().unit();
        assert(target);

        target->putDamage(this, {1}, el);

        if (auto *bmu = dynamic_cast<BasicMeleeUnit *>(target))
            putDamage(bmu, {_defence_multiplier}, el);
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
            && position() != pos
            && position().distance(pos) <= shootingRange();
    }



    BaseUnit::DamageSpec
    BasicCatapult::damageMultipler(const BaseUnit *unit) const
    {
        return (dynamic_cast<const BasicRangedUnit *>(unit)
                ? DamageSpec{0}
                : BaseUnit::damageMultipler(unit));
    }

    BasicCatapult::DeltaXY
    BasicCatapult::positionDelta(const GamePos &target) const
    {
        GamePos pos = position();
        return {(double)(target.x() - pos.x()),
                (double)(target.y() - pos.y())};
    }

    GamePos
    BasicCatapult::alterTargetPos(
        const GamePos &pos,
        const BasicCatapult::DeltaXY &vec,
        const BasicCatapult::Delta &delta)
    {
        Delta actual {
            std::uniform_real_distribution<>{
                -delta.tangential, delta.tangential}(global_random),
            std::uniform_real_distribution<>{
                -delta.normal, delta.normal}(global_random)};
        DeltaXY dxy = vec.apply(actual);
        int dx = round(dxy.x),
            dy = round(dxy.y);

        return GamePos{pos.map(), pos.x() + dx, pos.y() + dy};
    }

    void
    BasicCatapult::attack(const GamePos &pos, events::EventLoop *el)
    {
        assert(pos.valid());

        GamePos actual = alterTargetPos(
            pos, positionDelta(pos), getDelta(pos));
        if (!actual.valid())
            return;

        if (BaseUnit *unit = actual.cell().unit())
            unit->putDamage(this, {1}, el);
    }

    bool
    BasicCatapult::canAttack(const GamePos &pos) const
    {
        MinMaxRange range = shootingMinMaxRange();
        double dist = position().distance(pos);

        return dist >= range.min && dist <= range.max;
    }

}
