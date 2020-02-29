#include "game.hpp"
#include "event.hpp"


void
EventLoop::process()
{
    while (!_events.empty()) {
        Event *ev = _events.front();
        _events.pop();
        ev->execute(this);
        delete ev;
    }
}

void
Damage::execute(EventLoop *el)
{
    el->handle(this);
    unit->takeDamage(dmg);
    if (!unit->alive())
        el->push_back(new Death {unit});
}

void
Death::execute(EventLoop *el)
{
    el->handle(this);
    unit->die();
}
