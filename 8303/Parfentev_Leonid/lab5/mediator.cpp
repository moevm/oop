#include "point.hpp"
#include "map.hpp"
#include "event.hpp"
#include "event_types.hpp"
#include "neutral_object.hpp"
#include "mediator.hpp"


MapInfo
Mediator::infoAt(Vec2 pt)
{
    return _map->infoAt(pt);
}

Vec2
Mediator::mapSize()
{
    return {_map->width(),
            _map->height()};
}

bool
Mediator::moveUnitTo(Unit *u, Vec2 to)
{
    auto ito = _map->iterAt(to);
    
    if (ito.unit()
        || !u->canMove(ito)) {
        return false;
    }

    Vec2 from = u->position();

    _map->removeUnitAt(from);
    _map->addUnit(u, to);

    u->emit(new events::UnitMoved {u, from});
    return true;
}

bool
Mediator::attackTo(Unit *u, Vec2 to)
{
    auto ito = _map->iterAt(to);

    if (!ito.unit()
        || !u->canAttackTo(ito)) {
        return false;
    }

    auto pos = u->actualPosition(ito);
    Unit *t = pos.unit();

    u->emit(new events::UnitAttacked {u, pos.point(), t});

    if (t) {
        t->emit(new events::UnitWasAttacked {u, t});

        auto damage_pair = u->baseAttack(pos);
        auto damage_spec = t->actualDamage(damage_pair.first,
                                           damage_pair.second);
        int dmg = damage_spec.evaluate();

        t->takeDamage(dmg);
    }

    return true;
}

bool
Mediator::useObject(Unit *u)
{
    auto iter = _map->iterAt(u->position());

    NeutralObject *n = iter.neutralObject();

    if (!n
        || !n->canUse(u)) {
        return false;
    }

    n->onUse(u, this);

    u->emit(new events::UnitUsedObject {u, n});

    return true;
}

bool
Mediator::spawnUnit(Unit *u, Vec2 at)
{
    return !_map->addUnit(u, at).null();
}

bool
Mediator::teleportUnit(Unit *u, Vec2 to)
{
    auto ito = _map->iterAt(to);

    if (ito.unit()) {
        return false;
    }

    Vec2 from = u->position();

    _map->removeUnitAt(from);
    _map->addUnit(u, to);

    u->emit(new events::UnitTeleported {u, from});
    return true;
}
