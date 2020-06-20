#ifndef _H_NEUTRAL_OBJECT_TYPES_HPP
#define _H_NEUTRAL_OBJECT_TYPES_HPP

#include <random>

#include "neutral_object.hpp"
#include "mediator.hpp"
#include "map.hpp"
#include "unit.hpp"

#include "ranged_units.hpp"
#include "common_policies.hpp"

#include "storable.hpp"
#include "common_storables.hpp"


class ExtendedShootingRange: public NestedAttack {
    double _delta;

public:
    explicit ExtendedShootingRange(AttackPolicy *p=nullptr,
                                   double delta=0)
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

    virtual void
    store(std::ostream &os) const override
    {
        os << "ap_extended " << _delta << "\n";
        attackPolicy()->store(os);
    }

    virtual bool
    restore(std::istream &is, RestorerTable *tab)
    {
        is >> _delta;
        return !is.fail() && NestedAttack::restore(is, tab);
    }
};



namespace objects {

    class HealingWell: public NeutralObject {
    public:
        virtual void
        onUse(Unit *u, Mediator *) override
        {
            u->heal(25);
        }

        TRIVIALLY_STORABLE("n_healingwell");
    };

    class Tower: public NeutralObject {
        AttackPolicy *_prev;
        ExtendedShootingRange *_cur = nullptr;

    public:
        virtual bool
        canUse(const Unit *u) override
        {
            return dynamic_cast<const BasicRangedUnit *>(u);
        }

        virtual void
        onUse(Unit *u, Mediator *) override
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

        TRIVIALLY_STORABLE("n_tower");
    };

    class TunnelsEntrance: public NeutralObject {
    public:
        virtual void
        onUse(Unit *u, Mediator *m) override
        {
            static const int w = 5;

            Vec2 at = u->position();

            int max_n = 0;
            for (int j = -w; j <= w; ++j) {
                for (int i = -w; i <= w; ++i) {
                    auto iter = at.shifted({i, j});
                    if (m->infoAt(iter).unit() == nullptr) {
                        ++max_n;
                    }
                }
            }

            std::uniform_int_distribution<> distr {0, max_n-1};
            int n = distr(global_random);

            Vec2 dest;
            for (int j = -w; j <= w; ++j) {
                for (int i = -w; i <= w; ++i) {
                    auto iter = at.shifted({i, j});
                    if (m->infoAt(iter).unit() != nullptr) {
                        continue;
                    }
                    if (!--n) {
                        dest = iter;
                        break;
                    }
                }
            }

            m->teleportUnit(u, dest);
        }

        TRIVIALLY_STORABLE("n_tunnelentrance");
    };

    class WeaponSmiths: public NeutralObject {
    public:
        class UnitFilter: public Storable {
        public:
            virtual bool
            applicable(const Unit *u) =0;
        };

        template<typename U>
        class SimpleUnitFilter: public UnitFilter{
        public:
            virtual bool
            applicable(const Unit *u) override
            {
                return dynamic_cast<const U *>(u);
            }
        };

        class MeleeUnitFilter:
            public SimpleUnitFilter<units::Swordsman> {
            TRIVIALLY_STORABLE("uf_melee");
        };

        class RangedUnitFilter:
            public SimpleUnitFilter<units::Swordsman> {
            TRIVIALLY_STORABLE("uf_ranged");
        };

        class CatapultUnitFilter:
            public SimpleUnitFilter<units::Swordsman> {
            TRIVIALLY_STORABLE("uf_catapult");
        };

    private:
        double _mul;
        UnitFilter *_filter;

    public:
        explicit WeaponSmiths(double mul=0, UnitFilter *filter=nullptr)
            :_mul{mul}, _filter{filter} {}

        virtual bool
        canUse(const Unit *u) override
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
        onUse(Unit *u, Mediator *) override
        {
            auto *prev = u->attackPolicy();
            auto *new_p = new MultiplierAttackPolicy {prev, _mul};
            u->setAttackPolicy(new_p);
        }

        virtual void
        store(std::ostream &os) const override
        {
            os << "n_weaponsmiths " << _mul << "\n";
            if (_filter) {
                _filter->store(os);
            } else {
                os << "end\n";
            }
        }

        virtual bool
        restore(std::istream &is, RestorerTable *tab)
        {
            Storable *s = tab->restore(is);

            if (auto *uf = dynamic_cast<UnitFilter *>(s)) {
                _filter = uf;
            } else if (dynamic_cast<StorableEnd *>(s)) {
                _filter = nullptr;
                delete s;
            } else {
                delete s;
                return false;
            }

            return true;
        }
    };

}

#endif
