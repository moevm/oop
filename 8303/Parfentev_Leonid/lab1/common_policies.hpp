#ifndef _H_COMMON_POLICIES_HPP
#define _H_COMMON_POLICIES_HPP

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

class DefenseLevelDeco: public DefensePolicy {
    // Controls nested policy lifetime
    DefensePolicy *_p;
    AttackKind _kind;
    double _lvl;

public:
    DefenseLevelDeco(DefensePolicy *p,
                     AttackKind kind,
                     double level)
        :_p{p}, _kind{kind}, _lvl{level} {}

    ~DefenseLevelDeco()
    {
        delete _p;
    }

    virtual DamageSpec
    actualDamage(const Unit *u, AttackKind kind, int base) override
    {
        if (kind == _kind)
            return defense_level(_lvl, base);
        return _p->actualDamage(u, kind, base);
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

#endif
