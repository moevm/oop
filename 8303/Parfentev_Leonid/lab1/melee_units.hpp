#ifndef _H_MELEE_UNITS_HPP
#define _H_MELEE_UNITS_HPP

#include <utility>

#include "point.hpp"
#include "unit.hpp"
#include "common_policies.hpp"


class MeleeAttack: public AttackPolicy {
    AttackKind _kind;
    int _base_damage;

public:
    MeleeAttack(AttackKind kind, int base_dmg)
        :_kind{kind}, _base_damage{base_dmg} {}

    virtual bool
    canAttackTo(const Unit *u, MapIter to) override
    {
        return to.unit() != nullptr
            && to.point().adjacent(u->position());
    }

    virtual std::pair<AttackKind, int>
    baseAttack(const Unit *u, MapIter)
    {
        return std::make_pair(
            _kind,
            int(_base_damage * u->relativeHealth()));
    }
};

class BasicMeleeUnit: public Unit {
public:
    BasicMeleeUnit(int speed,
                   AttackKind attack_kind,
                   int base_dmg,
                   DefensePolicy *def,
                   int base_health)
        :Unit{new BasicMovement {speed},
              new MeleeAttack {attack_kind, base_dmg},
              def, base_health} {}
};

namespace units {
    class Swordsman: public BasicMeleeUnit {
    public:
        Swordsman() :BasicMeleeUnit{
            2,
            AttackKind::sword, 40,
            DefenseLevelDeco::good_defense_deco(
                AttackKind::spear,
                DefenseLevelDeco::vulnerability_deco(
                    AttackKind::cavalry,
                    new BasicDefense {})),
            100} {}
    };

    class Spearsman: public BasicMeleeUnit {
    public:
        Spearsman() :BasicMeleeUnit{
            2,
            AttackKind::spear, 75,
            DefenseLevelDeco::good_defense_deco(
                AttackKind::cavalry,
                DefenseLevelDeco::vulnerability_deco(
                    AttackKind::spear,
                    new BasicDefense {})),
            75} {}
    };

    class Cavalry: public BasicMeleeUnit {
    public:
        Cavalry() :BasicMeleeUnit{
            3,
            AttackKind::cavalry, 50,
            DefenseLevelDeco::good_defense_deco(
                AttackKind::sword,
                DefenseLevelDeco::vulnerability_deco(
                    AttackKind::spear,
                    new BasicDefense {})),
            75} {}
    };
}

#endif
