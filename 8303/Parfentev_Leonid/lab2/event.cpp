#include "event.hpp"

void
EventEmitter::emit_shared(Event *e)
{
    for (auto iter = _listeners.begin(); iter != _listeners.end();) {
        auto *listener = *iter++;
        // note: the listener may safely unsubscribe when handling the
        // event.
        listener->handle(e);
    }
}

void
EventEmitter::emit(Event *e)
{
    emit_shared(e);
    delete e;
}

void
EventEmitter::subscribe(EventListener *l)
{
    _listeners.insert(l);
}

void
EventEmitter::unsubscribe(EventListener *l)
{
    _listeners.erase(l);
}
