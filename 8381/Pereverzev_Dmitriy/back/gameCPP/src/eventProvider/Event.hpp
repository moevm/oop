#ifndef Event_hpp
#define Event_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <node.h>



class EventProvider;
class Event
{
private:
    std::string sEventId;
    EventProvider *source;

    v8::Local<v8::Value> data;

public:
    Event(std::string sEventId, v8::Local<v8::Value> data, EventProvider *source);
    Event(std::string sEventId, EventProvider *source);

    std::string getSEventId();
    EventProvider *getSource();
    v8::Local<v8::Value> getData();

    void setSEventId(std::string sEventId);
    void setSource(EventProvider *source);
    void setData(v8::Local<v8::Value> data);
};

#endif /* Event_hpp */