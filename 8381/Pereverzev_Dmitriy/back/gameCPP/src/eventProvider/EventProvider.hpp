
#ifndef EventProvider_hpp
#define EventProvider_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "Event.hpp"
#include "../simplifiedConverter/SimplifiedConverter.hpp"

class EventProvider : public SimplifiedConverter
{
private:
    std::vector<Event> observers;

public:
    void detachEvent(std::string sEventId, EventProvider *object);
    void attachEvent(std::string sEventId, EventProvider *object);
    void fireEvent(std::string sEventId, v8::Local<v8::Value> data);
    void fireEvent(std::string sEventId);
    virtual void eventHandler(Event *event) = 0;
};

#endif /* EventProvider_hpp */
