#ifndef Command_hpp
#define Command_hpp

#include <node.h>
#include "../simplifiedConverter/SimplifiedConverter.hpp"
#include "../eventProvider/EventProvider.hpp"
#include "../except/Except.hpp"
#include "../TypeСonstants.hpp"

class Command : public EventProvider
{
protected:
public:
    virtual void execute(v8::Local<v8::Value> request);
    void eventHandler(Event *event) override;
};

#endif /* Command_hpp */
