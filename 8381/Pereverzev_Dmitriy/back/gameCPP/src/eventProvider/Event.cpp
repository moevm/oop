#include "Event.hpp"

Event::Event(std::string sEventId, v8::Local<v8::Value> data, EventProvider *source) : sEventId(sEventId), data(data)
{
    this->source = source;
}

Event::Event(std::string sEventId, EventProvider *source) : sEventId(sEventId)
{
    this->source = source;
}

std::string Event::getSEventId()
{
    return sEventId;
}

EventProvider *Event::getSource()
{
    return source;
}

v8::Local<v8::Value> Event::getData()
{
    return data;
}

void Event::setSEventId(std::string sEventId)
{
    this->sEventId = sEventId;
}

void Event::setSource(EventProvider *source)
{
    this->source = source;
}
void Event::setData(v8::Local<v8::Value> data)
{
    this->data = data;
}
