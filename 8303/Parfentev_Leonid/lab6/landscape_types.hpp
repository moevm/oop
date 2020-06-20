#ifndef _H_LANDSCAPE_TYPES_HPP
#define _H_LANDSCAPE_TYPES_HPP

#include "landscape.hpp"
#include "unit.hpp"
#include "map.hpp"
#include "common_policies.hpp"
#include "storable.hpp"


namespace landscapes {

    // Swamp: max speed is 1; attacking is forbidden
    class Swamp: public Landscape {
        ModifyingMovePolicy *_p;
        AttackPolicy *_prev, *_cur;

    public:
        virtual void onEnter(Unit *u) override
        {
            _p = new ModifyingMovePolicy {u->movePolicy(), 1};
            u->setMovePolicy(_p);

            _prev = u->attackPolicy();
            _cur = new AttackForbidden {};
            u->setAttackPolicy(_cur);
        }

        virtual void onLeave(Unit *u) override
        {
            if (auto *mpc = u->findMoveContainerOf(_p)) {
                mpc->setMovePolicy(_p->movePolicy());
                _p->setMovePolicy(nullptr);
                delete _p;
                _p = nullptr;
            }

            // our policy might’ve been wrapped into something
            if (auto *apc = u->findAttackContainerOf(_cur)) {
                apc->setAttackPolicy(_prev);
                delete _cur;
                _cur = nullptr;
            }
        }

        TRIVIALLY_STORABLE("l_swamp");
    };

    class Forest: public Landscape {
        DefensePolicy *_prev;
        MultiplierDefensePolicy *_cur;

    public:
        virtual void onEnter(Unit *u) override
        {
            _prev = u->defensePolicy();
            _cur = new MultiplierDefensePolicy {_prev, 2.0};
            u->setDefensePolicy(_cur);
        }

        virtual void onLeave(Unit *u) override
        {
            if (auto *dpc = u->findDefenseContainerOf(_cur)) {
                dpc->setDefensePolicy(_prev);
                _cur->setDefensePolicy(nullptr);
                delete _cur;
                _cur = nullptr;
            }
        }

        TRIVIALLY_STORABLE("l_forest");
    };
}

#endif
