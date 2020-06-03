#include "EventProvider.hpp"

void EventProvider::attachEvent(std::string sEventId, EventProvider *object)
{
    Event *observer = new Event(sEventId, object);
    observers.push_back(*observer);
};
void EventProvider::detachEvent(std::string sEventId, EventProvider *object)
{
    std::__1::__wrap_iter<Event *> index = std::find_if(observers.begin(), observers.end(), [&sEventId](Event &vi) { return (vi.getSEventId() == sEventId); });
    if (index != observers.end())
        observers.erase(index);
};

void EventProvider::fireEvent(std::string sEventId, v8::Local<v8::Value> data)
{

    Event *eventObject = new Event(sEventId, data, this);
    std::for_each(observers.begin(), observers.end(), [eventObject, &sEventId](Event &event) {
        if (event.getSEventId() == sEventId || event.getSEventId() == "log")
            (event.getSource()->eventHandler)(eventObject);
    });
    delete eventObject;
}

void EventProvider::fireEvent(std::string sEventId)
{

    v8::Local<v8::Value> undef;
    fireEvent(sEventId, undef);
}
