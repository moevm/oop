#ifndef _H_COMMON_POLICIES_HPP
#define _H_COMMON_POLICIES_HPP

#include <utility>

#include "unit.hpp"
#include "map.hpp"
#include "pathfinder.hpp"


class BasicMovement: public MovePolicy {
    int _steps_per_turn;

public:
    explicit BasicMovement(int n=0)
        :_steps_per_turn{n} {}

    virtual bool
    canMove(const Unit *u, MapIter to) override
    {
        MapIter from = to.otherAt(u->position());
        PathFinder pf {from, to, _steps_per_turn};
        return pf.run();
    }

    virtual void
    store(std::ostream &os) const override
    {
        os << "mp_basic " << _steps_per_turn << "\n";
    }

    virtual bool
    restore(std::istream &is, RestorerTable *)
    {
        is >> _steps_per_turn;
        return !is.fail();
    }
};

class NestedMovement: public MovePolicy,
                      public MovePolicyContainer {
public:
    using MovePolicyContainer::MovePolicyContainer;

    virtual bool
    restore(std::istream &is, RestorerTable *tab)
    {
        Storable *s = tab->restore(is);
        if (auto *p = dynamic_cast<MovePolicy *>(s)) {
            setMovePolicy(p);
            return true;
        }
        delete s;
        return false;
    }
};

class ModifyingMovePolicy: public NestedMovement {
    int _max;

public:
    explicit ModifyingMovePolicy(MovePolicy *p=nullptr, int max_dist=0)
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

    virtual void
    store(std::ostream &os) const override
    {
        os << "mp_modifyiing " << _max << "\n";
        movePolicy()->store(os);
    }

    virtual bool
    restore(std::istream &is, RestorerTable *tab)
    {
        is >> _max;
        return !is.fail() && NestedMovement::restore(is, tab);
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

    virtual void
    store(std::ostream &os) const override
    {
        os << "dp_basic " << _lvl << "\n";
    }

    virtual bool
    restore(std::istream &is, RestorerTable *)
    {
        is >> _lvl;
        return !is.fail();
    }
};

class NestedDefense: public DefensePolicy,
                     public DefensePolicyContainer {
public:
    using DefensePolicyContainer::DefensePolicyContainer;

    virtual bool
    restore(std::istream &is, RestorerTable *tab)
    {
        Storable *s = tab->restore(is);
        if (auto *p = dynamic_cast<DefensePolicy *>(s)) {
            setDefensePolicy(p);
            return true;
        }
        delete s;
        return false;
    }
};

class DefenseLevelDeco: public NestedDefense {
    // Controls nested policy lifetime
    AttackKind _kind;
    double _lvl;

public:
    explicit DefenseLevelDeco(DefensePolicy *p=0,
                              AttackKind kind=AttackKind::invalid,
                              double level=0)
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

    virtual void
    store(std::ostream &os) const override
    {
        os << "dp_level_deco " << static_cast<int>(_kind)
           << " " << _lvl << "\n";
        defensePolicy()->store(os);
    }

    virtual bool
    restore(std::istream &is, RestorerTable *tab)
    {
        int x;
        is >> x;
        _kind = static_cast<AttackKind>(x);
        is >> _lvl;

        return !is.fail() && NestedDefense::restore(is, tab);
    }
};

class MultiplierDefensePolicy: public NestedDefense {
    double _mul;

public:
    explicit MultiplierDefensePolicy(DefensePolicy *p=nullptr,
                                     double mul=0)
        :NestedDefense{p}, _mul{mul} {}

    virtual DamageSpec
    actualDamage(const Unit *u, AttackKind kind, int base) override
    {
        DamageSpec ds = defensePolicy()->actualDamage(u, kind, base);
        ds.scale(1/_mul);
        return ds;
    }

    virtual void
    store(std::ostream &os) const override
    {
        os << "dp_multiplier " << _mul << "\n";
        defensePolicy()->store(os);
    }

    virtual bool
    restore(std::istream &is, RestorerTable *tab)
    {
        is >> _mul;
        return !is.fail() && NestedDefense::restore(is, tab);
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

    TRIVIALLY_STORABLE("ap_forbidden");
};

class NestedAttack: public AttackPolicy,
                    public AttackPolicyContainer {
public:
    using AttackPolicyContainer::AttackPolicyContainer;

    virtual bool
    restore(std::istream &is, RestorerTable *tab)
    {
        Storable *s = tab->restore(is);
        if (auto *p = dynamic_cast<AttackPolicy *>(s)) {
            setAttackPolicy(p);
            return true;
        }
        delete s;
        return false;
    }
};

class MultiplierAttackPolicy: public NestedAttack {
    double _mul;

public:
    explicit MultiplierAttackPolicy(AttackPolicy *p=nullptr,
                                    double mul=0)
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

    virtual void
    store(std::ostream &os) const override
    {
        os << "ap_multiplier " << _mul << "\n";
        attackPolicy()->store(os);
   }

    virtual bool
    restore(std::istream &is, RestorerTable *tab)
    {
        is >> _mul;
        return !is.fail() && NestedAttack::restore(is, tab);
    }
};


#endif
