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

    const BasicMeleeUnit::Config
    Swordsman::_cfg = {
        .baseHealth = 100,
        .baseDamage = 40,
        .damageSpread = .10,
        .basicSpeed = 2,
    };

    double
    Swordsman::typeDamageMultiplier(const BasicMeleeUnit *unit) const
    {
        return dynamic_cast<const Rider *>(unit) ? 2.0 : 1.0;
    }

    const BasicMeleeUnit::Config
    Spearsman::_cfg = {
        .baseHealth = 80,
        .baseDamage = 35,
        .damageSpread = .05,
        .basicSpeed = 2,
    };

    double
    Spearsman::typeDamageMultiplier(const BasicMeleeUnit *unit) const
    {
        return dynamic_cast<const Swordsman *>(unit) ? 1.5 : 1.0;
    }

    const BasicMeleeUnit::Config
    Rider::_cfg = {
        .baseHealth = 75,
        .baseDamage = 50,
        .damageSpread = .10,
        .basicSpeed = 3,
    };

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
            && point().distance(iter.point()) <= _c->shootingRange;
    }

    const BasicRangedUnit::Config
    Archer::_cfg = {
        .baseHealth = 70,
        .baseDamage = 45,
        .damageSpread = .20,
        .shootingRange = 3,
        .distancePower = .20,
        .basicSpeed = 2,
    };

    const BasicRangedUnit::Config
    Slinger::_cfg = {
        .baseHealth = 70,
        .baseDamage = 60,
        .damageSpread = .25,
        .shootingRange = 2,
        .distancePower = .60,
        .basicSpeed = 2,
    };



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
        double dist = point().distance(iter.point());

        return dist >= _c->shootingRange.min
            && dist <= _c->shootingRange.max;
    }

    const BasicCatapult::Config
    Onager::_cfg = {
        .baseHealth = 20,
        .baseDamage = 150,
        .damageSpread = .10,
        .shootingRange = {2, 7},
        .basicSpeed = 1,
        .baseCoordDelta = {.3, .1},
    };

    const BasicCatapult::Config
    BoltThrower::_cfg = {
        .baseHealth = 20,
        .baseDamage = 125,
        .damageSpread = .10,
        .shootingRange = {1, 5},
        .basicSpeed = 1,
        .baseCoordDelta = {.09, .03},
    };

}
