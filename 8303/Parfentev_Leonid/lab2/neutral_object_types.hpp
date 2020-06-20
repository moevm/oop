#ifndef _H_NEUTRAL_OBJECT_TYPES_HPP
#define _H_NEUTRAL_OBJECT_TYPES_HPP

#include <random>

#include "neutral_object.hpp"
#include "map.hpp"
#include "unit.hpp"

#include "ranged_units.hpp"
#include "common_policies.hpp"


class ExtendedShootingRange: public NestedAttack {
    double _delta;

public:
    ExtendedShootingRange(AttackPolicy *p, double delta)
        :NestedAttack{p}, _delta{delta} {}

    virtual bool
    canAttackTo(const Unit *u, MapIter to) override
    {
        double dist = to.point().distance(u->position());
        auto *a = dynamic_cast<RangedAttack *>(attackPolicy());
        return dist >= a->minRange()
            && dist <= (a->maxRange() + _delta);
    }

    virtual MapIter
    actualPosition(const Unit *u, MapIter to) override
    {
        return attackPolicy()->actualPosition(u, to);
    }

    virtual std::pair<AttackKind, int>
    baseAttack(const Unit *u, MapIter to) override
    {
        return attackPolicy()->baseAttack(u, to);
    }
};



namespace objects {

    class HealingWell: public NeutralObject {
    public:
        virtual void
        onUse(Unit *u, MapIter) override
        {
            u->heal(25);
        }
    };

    class Tower: public NeutralObject {
        AttackPolicy *_prev;
        ExtendedShootingRange *_cur = nullptr;

    public:
        virtual bool
        canUse(const Unit *u, MapIter) override
        {
            return dynamic_cast<const BasicRangedUnit *>(u);
        }

        virtual void
        onUse(Unit *u, MapIter) override
        {
            _prev = u->attackPolicy();
            _cur = new ExtendedShootingRange {_prev, 5};
            u->setAttackPolicy(_cur);
        }

        virtual void
        onLeave(Unit *u) override
        {
            if (_cur == nullptr) {
                return;
            }
            if (auto *apc = u->findAttackContainerOf(_cur)) {
                apc->setAttackPolicy(_prev);
                _cur->setAttackPolicy(nullptr);
                delete _cur;
                _cur = nullptr;
            }
        }
    };

    class TunnelsEntrance: public NeutralObject {
    public:
        virtual void
        onUse(Unit *, MapIter at) override
        {
            static const int w = 5;

            int max_n = 0;
            for (int j = -w; j <= w; ++j) {
                for (int i = -w; i <= w; ++i) {
                    auto iter = at.shifted({i, j});
                    if (iter.unit() == nullptr) {
                        ++max_n;
                    }
                }
            }

            std::uniform_int_distribution<> distr {0, max_n-1};
            int n = distr(global_random);

            MapIter dest = MapIter::makeNull();
            for (int j = -w; j <= w; ++j) {
                for (int i = -w; i <= w; ++i) {
                    auto iter = at.shifted({i, j});
                    if (iter.unit() != nullptr) {
                        continue;
                    }
                    if (!--n) {
                        dest = iter;
                        break;
                    }
                }
            }

            at.moveUnitTo(dest);
        }
    };

    class WeaponSmiths: public NeutralObject {
    public:
        class UnitFilter {
        public:
            virtual bool
            applicable(const Unit *u) =0;
        };

        template<typename U>
        class SimpleUnitFilter: public UnitFilter {
        public:
            virtual bool
            applicable(const Unit *u) override
            {
                return dynamic_cast<const U *>(u);
            }
        };

    private:
        double _mul;
        UnitFilter *_filter;

    public:
        explicit WeaponSmiths(double mul, UnitFilter *filter=nullptr)
            :_mul{mul}, _filter{filter} {}

        virtual bool
        canUse(const Unit *u, MapIter) override
        {
            if (_filter
                && !_filter->applicable(u)) {
                return false;
            }

            for (const AttackPolicyContainer *apc = u; apc;
                 apc = dynamic_cast<AttackPolicyContainer *>(
                     apc->attackPolicy())) {
                if (dynamic_cast<const MultiplierAttackPolicy *>(apc)) {
                    return false;
                }
            }

            return true;
        }

        virtual void
        onUse(Unit *u, MapIter) override
        {
            auto *prev = u->attackPolicy();
            auto *new_p = new MultiplierAttackPolicy {prev, _mul};
            u->setAttackPolicy(new_p);
        }
    };

}

#endif
