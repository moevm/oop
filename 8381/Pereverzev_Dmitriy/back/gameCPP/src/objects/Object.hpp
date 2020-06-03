
#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <string>

#include "../except/Except.hpp"
#include "../eventProvider/EventProvider.hpp"
#include "../TypeСonstants.hpp"

class Object : public EventProvider
{
protected:
    unsigned int objectType;
    unsigned int move = 0;
    std::string ID;
    std::string playerID;

public:
    unsigned int getObjectType();
    std::string getPlayerID();
    virtual v8::Local<v8::Object> getFullInfo();
    virtual bool isMoveable() = 0;
    virtual void operator+(Object *object) = 0;
};

#endif /* Object_hpp */