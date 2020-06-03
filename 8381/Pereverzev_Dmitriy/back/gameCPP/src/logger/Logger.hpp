
#ifndef Logger_hpp
#define Logger_hpp

#include <node.h>
#include "../eventProvider/EventProvider.hpp"

class Logger : public EventProvider
{

    void eventHandler(Event *event);
public:
    

    
    virtual void printLog(std::string strLog) = 0;
};

#endif /* Logger_hpp */
