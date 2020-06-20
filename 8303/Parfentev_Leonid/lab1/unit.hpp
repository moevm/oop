#ifndef _H_UNIT_HPP
#define _H_UNIT_HPP

#include <utility>
#include <random>
#include <math.h>

#include "map.hpp"


extern std::default_random_engine global_random;


class MovePolicy {
public:
    virtual bool canMove(const Unit *u, MapIter to) =0;
    virtual ~MovePolicy() {}
};

enum class AttackKind {
    sword, spear, cavalry, arrow, stone, rock, bolt,
};

// NOTE: can’t do area damage
class AttackPolicy {
public:
    virtual bool canAttackTo(const Unit *u, MapIter to) =0;

    virtual MapIter actualPosition(const Unit *, MapIter to)
    {
        return to;
    }

    // returns kind and base damage
    virtual std::pair<AttackKind, int>
    baseAttack(const Unit *u, MapIter to) =0;

    virtual ~AttackPolicy() {}
};

struct DamageSpec {
    int base_damage, damage_spread;

    int evaluate() const
    {
        std::uniform_int_distribution<>
            dist {-damage_spread, damage_spread};

        return base_damage + dist(global_random);
    }
};

class DefensePolicy {
protected:
    static DamageSpec
    make_spec(double base, double spread)
    {
        return DamageSpec{(int)base, (int)spread};
    }

    static DamageSpec
    defense_level(double k, int dmg)
    {
        return make_spec(round(1.0*dmg/k),
                         round(0.25*dmg/k));
    }

    static DamageSpec
    normal_defense(double dmg)
    {
        return defense_level(1.0, dmg);
    }

public:
    // returns base damage and spread
    virtual DamageSpec
    actualDamage(const Unit *u, AttackKind kind, int base) =0;

    virtual ~DefensePolicy() {}
};

class Unit: public Placeable {
    // Controls the lifetime of policies once they are given to the unit
    // through the constructor.
    MovePolicy *_move_policy;
    AttackPolicy *_attack_policy;
    DefensePolicy *_defence_policy;

    int _health, _base_health;

public:
    Unit(MovePolicy *move,
         AttackPolicy *attack,
         DefensePolicy *defense,
         int base_health)
        :_move_policy{move},
         _attack_policy{attack},
         _defence_policy{defense},
         _health{base_health},
         _base_health{base_health} {}

    ~Unit()
    {
        delete _move_policy;
        delete _attack_policy;
        delete _defence_policy;
    }

    int
    health() const { return _health; }
    int
    baseHealth() const { return _base_health; }
    double
    relativeHealth() const { return _health / (double)_base_health; }
    bool
    alive() const { return health() > 0; }

    void
    takeDamage(int dmg) { _health -= dmg; }

    bool
    canMove(MapIter to) const
    {
        return _move_policy->canMove(this, to);
    }

    bool
    canAttackTo(MapIter to) const
    {
        return _attack_policy->canAttackTo(this, to);
    }

    MapIter
    actualPosition(MapIter to) const
    {
        return _attack_policy->actualPosition(this, to);
    }

    std::pair<AttackKind, int>
    baseAttack(MapIter to) const
    {
        return _attack_policy->baseAttack(this, to);
    }

    DamageSpec
    actualDamage(AttackKind kind, int base) const
    {
        return _defence_policy->actualDamage(this, kind, base);
    }
};

#endif
