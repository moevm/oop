#include "map.hpp"
#include "unit.hpp"
#include "event.hpp"
#include "unit_types.hpp"


namespace units {

    BaseUnit::DamageSpec
    BasicMeleeUnit::damageMultipler(MapConstIter iter) const
    {
        auto dmg = BaseUnit::damageMultipler(iter);

        if (const auto *a =
            dynamic_cast<const BasicMeleeUnit *>(iter->unit()))
            dmg *= {typeDamageMultiplier(a)};

        return dmg;
    }

    bool
    BasicMeleeUnit::canAttack(MapConstIter iter) const
    {
        return iter->unit()
            && point().adjacent(iter.point());
    }


    void
    BasicMeleeUnit::attack(MapIter iter, events::EventLoop *el)
    {
        BaseUnit *target = iter->unit();
        assert(target);

        target->putDamage(iter.otherAt(point()), {1}, el);

        if (dynamic_cast<BasicMeleeUnit *>(target))
            putDamage(iter, {_defence_multiplier}, el);
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
    BasicRangedUnit::canAttack(MapConstIter iter) const
    {
        return iter->unit()
            && point() != iter.point()
            && point().distance(iter.point()) <= shootingRange();
    }



    BaseUnit::DamageSpec
    BasicCatapult::damageMultipler(MapConstIter iter) const
    {
        return (dynamic_cast<const BasicRangedUnit *>(iter->unit())
                ? DamageSpec{0}
                : BaseUnit::damageMultipler(iter));
    }

    BasicCatapult::DeltaXY
    BasicCatapult::pointDelta(const Point &target) const
    {
        return {(double)(target.x() - point().x()),
                (double)(target.y() - point().y())};
    }

    MapConstIter
    BasicCatapult::alterTargetPos(
        MapConstIter iter,
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

        return iter.otherAt(iter.point().shifted(dx, dy));
    }

    void
    BasicCatapult::attack(MapIter iter, events::EventLoop *el)
    {
        MapConstIter actual =
            alterTargetPos(iter,
                           pointDelta(iter.point()),
                           getDelta(iter));
        if (!actual.valid())
            return;

        if (BaseUnit *unit = actual->unit())
            unit->putDamage(iter, {1}, el);
    }

    bool
    BasicCatapult::canAttack(MapConstIter iter) const
    {
        MinMaxRange range = shootingMinMaxRange();
        double dist = point().distance(iter.point());

        return dist >= range.min && dist <= range.max;
    }

}
