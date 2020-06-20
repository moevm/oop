#ifndef _H_COMMON_POLICIES_HPP
#define _H_COMMON_POLICIES_HPP

#include <utility>

#include "unit.hpp"
#include "map.hpp"
#include "pathfinder.hpp"


class BasicMovement: public MovePolicy {
    int _steps_per_turn;

public:
    BasicMovement(int n)
        :_steps_per_turn{n} {}

    virtual bool
    canMove(const Unit *u, MapIter to) override
    {
        MapIter from = to.otherAt(u->position());
        PathFinder pf {from, to, _steps_per_turn};
        return pf.run();
    }
};

class NestedMovement: public MovePolicy,
                      public MovePolicyContainer {
public:
    using MovePolicyContainer::MovePolicyContainer;
};

class ModifyingMovePolicy: public NestedMovement {
    int _max;

public:
    ModifyingMovePolicy(MovePolicy *p, int max_dist)
        :NestedMovement{p}, _max{max_dist} {}

    virtual bool
    canMove(const Unit *u, MapIter to) override
    {
        MapIter from = to.otherAt(u->position());
        PathFinder pf {from, to, _max};
        if (!pf.run())
            return false;

        return movePolicy()->canMove(u, to);
    }
};



class BasicDefense: public DefensePolicy {
    double _lvl;

public:
    explicit BasicDefense(double level=1.0)
        :_lvl{level} {}

    virtual DamageSpec
    actualDamage(const Unit *, AttackKind, int base) override
    {
        return normal_defense(base);
    }
};

class NestedDefense: public DefensePolicy,
                     public DefensePolicyContainer {
public:
    using DefensePolicyContainer::DefensePolicyContainer;
};

class DefenseLevelDeco: public NestedDefense {
    // Controls nested policy lifetime
    AttackKind _kind;
    double _lvl;

public:
    DefenseLevelDeco(DefensePolicy *p,
                     AttackKind kind,
                     double level)
        :NestedDefense{p}, _kind{kind}, _lvl{level} {}

    virtual DamageSpec
    actualDamage(const Unit *u, AttackKind kind, int base) override
    {
        if (kind == _kind)
            return defense_level(_lvl, base);
        return defensePolicy()->actualDamage(u, kind, base);
    }

    static DefenseLevelDeco *
    defense_level_deco(AttackKind kind, double lvl, DefensePolicy *p)
    {
        return new DefenseLevelDeco {p, kind, lvl};
    }

    static DefenseLevelDeco *
    good_defense_deco(AttackKind kind, DefensePolicy *p)
    {
        return defense_level_deco(kind, 2.0, p);
    }

    static DefenseLevelDeco *
    vulnerability_deco(AttackKind kind, DefensePolicy *p)
    {
        return defense_level_deco(kind, 0.5, p);
    }
};

class MultiplierDefensePolicy: public NestedDefense {
    double _mul;

public:
    MultiplierDefensePolicy(DefensePolicy *p, double mul)
        :NestedDefense{p}, _mul{mul} {}

    virtual DamageSpec
    actualDamage(const Unit *u, AttackKind kind, int base) override
    {
        DamageSpec ds = defensePolicy()->actualDamage(u, kind, base);
        ds.scale(1/_mul);
        return ds;
    }
};



class AttackForbidden: public AttackPolicy {
public:
    using AttackPolicy::AttackPolicy;

    virtual bool
    canAttackTo(const Unit *, MapIter) override
    {
        return false;
    }

    virtual std::pair<AttackKind, int>
    baseAttack(const Unit *, MapIter) override
    {
        return std::make_pair(AttackKind::invalid, 0);
    }
};

class NestedAttack: public AttackPolicy,
                    public AttackPolicyContainer {
public:
    using AttackPolicyContainer::AttackPolicyContainer;
};

class MultiplierAttackPolicy: public NestedAttack {
    double _mul;

public:
    MultiplierAttackPolicy(AttackPolicy *p, double mul)
        :NestedAttack{p}, _mul{mul} {}

    virtual bool
    canAttackTo(const Unit *u, MapIter to) override
    {
        return attackPolicy()->canAttackTo(u, to);
    }

    virtual MapIter
    actualPosition(const Unit *u, MapIter to) override
    {
        return attackPolicy()->actualPosition(u, to);
    }

    virtual std::pair<AttackKind, int>
    baseAttack(const Unit *u, MapIter to) override
    {
        auto ba = attackPolicy()->baseAttack(u, to);
        return std::make_pair(ba.first, (int)(ba.second * _mul));
    }
};


#endif
