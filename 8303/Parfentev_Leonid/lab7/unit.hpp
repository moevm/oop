#ifndef _H_UNIT_HPP
#define _H_UNIT_HPP

#include <utility>
#include <random>
#include <math.h>

#include "event.hpp"
#include "event_types.hpp"
#include "object_w_health.hpp"
#include "map.hpp"


extern std::default_random_engine global_random;


class MovePolicy: public Storable {
public:
    virtual bool canMove(const Unit *u, MapIter to) =0;
    virtual ~MovePolicy() {}
};

enum class AttackKind {
    invalid, sword, spear, cavalry, arrow, stone, rock, bolt,
};

// NOTE: can’t do area damage
class AttackPolicy: public Storable {
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

    void
    scale(double k)
    {
        base_damage *= k;
        damage_spread *= k;
    }

    DamageSpec
    scaled(double k) const
    {
        auto ds = *this;
        ds.scale(k);
        return ds;
    }

    int evaluate() const
    {
        std::uniform_int_distribution<>
            dist {-damage_spread, damage_spread};

        return base_damage + dist(global_random);
    }
};

class DefensePolicy: public Storable {
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

class MovePolicyContainer {
    MovePolicy *_mp;

public:
    MovePolicyContainer(MovePolicy *mp) :_mp{mp} {}

    MovePolicy *movePolicy() const { return _mp; }
    void setMovePolicy(MovePolicy *mp)
    {
        _mp = mp;
    }
    virtual ~MovePolicyContainer() { delete _mp; }

    MovePolicyContainer *
    findMoveContainerOf(const MovePolicy *mp)
    {
        for (MovePolicyContainer *mpc = this; mpc;
             mpc = dynamic_cast<MovePolicyContainer *>(
                 mpc->movePolicy())) {
            if (mpc->movePolicy() == mp) {
                return mpc;
            }
        }
        return nullptr;
    }
};

class DefensePolicyContainer {
    DefensePolicy *_dp;

public:
    DefensePolicyContainer(DefensePolicy *dp) :_dp{dp} {}

    DefensePolicy *defensePolicy() const { return _dp; }
    void setDefensePolicy(DefensePolicy *dp)
    {
        _dp = dp;
    }
    virtual ~DefensePolicyContainer() { delete _dp; }

    DefensePolicyContainer *
    findDefenseContainerOf(const DefensePolicy *dp)
    {
        for (DefensePolicyContainer *dpc = this; dpc;
             dpc = dynamic_cast<DefensePolicyContainer *>(
                 dpc->defensePolicy())) {
            if (dpc->defensePolicy() == dp) {
                return dpc;
            }
        }
        return nullptr;
    }
};

class AttackPolicyContainer {
    AttackPolicy *_ap;

public:
    AttackPolicyContainer(AttackPolicy *ap) :_ap{ap} {}

    AttackPolicy *attackPolicy() const { return _ap; }
    void setAttackPolicy(AttackPolicy *ap)
    {
        _ap = ap;
    }
    virtual ~AttackPolicyContainer() { delete _ap; }

    AttackPolicyContainer *
    findAttackContainerOf(const AttackPolicy *ap)
    {
        for (AttackPolicyContainer *apc = this; apc;
             apc = dynamic_cast<AttackPolicyContainer *>(
                 apc->attackPolicy())) {
            if (apc->attackPolicy() == ap) {
                return apc;
            }
        }
        return nullptr;
    }
};

class Unit: public Placeable,
            public ObjectWithHealth,
            public EventEmitter,
            public MovePolicyContainer,
            public DefensePolicyContainer,
            public AttackPolicyContainer {
public:
    Unit(MovePolicy *move,
         AttackPolicy *attack,
         DefensePolicy *defense,
         int base_health)
        :ObjectWithHealth{base_health},
         MovePolicyContainer{move},
         DefensePolicyContainer{defense},
         AttackPolicyContainer{attack} {}

    virtual void
    heal(int hp)
    {
        emit(new events::UnitGetsHealed {this, hp});
        ObjectWithHealth::heal(hp);
    }

    virtual void
    takeDamage(int dmg)
    {
        if (!alive()) {
            return;
        }

        emit(new events::UnitTakesDamage {this, dmg});

        ObjectWithHealth::takeDamage(dmg);

        if (!alive()) {
            emit(new events::UnitDeath {this});
        }
    }

    bool
    canMove(MapIter to) const
    {
        return movePolicy()->canMove(this, to);
    }

    bool
    canAttackTo(MapIter to) const
    {
        return attackPolicy()->canAttackTo(this, to);
    }

    MapIter
    actualPosition(MapIter to) const
    {
        return attackPolicy()->actualPosition(this, to);
    }

    std::pair<AttackKind, int>
    baseAttack(MapIter to) const
    {
        return attackPolicy()->baseAttack(this, to);
    }

    DamageSpec
    actualDamage(AttackKind kind, int base) const
    {
        return defensePolicy()->actualDamage(this, kind, base);
    }

    // override to add type symbol!
    virtual void store(std::ostream &os) const override;
    virtual bool restore(std::istream &is,
                         RestorerTable *tab) override;

    virtual ~Unit() override
    {
        if (alive()) {
            emit(new events::UnitLiveDeleted {this});
        }
    }
};

#define UNIT_STORABLE_NAME(n)                   \
    virtual void                                \
    store(std::ostream &os) const override      \
    {                                           \
        os << n "\n";                           \
        Unit::store(os);                        \
    }

#endif
