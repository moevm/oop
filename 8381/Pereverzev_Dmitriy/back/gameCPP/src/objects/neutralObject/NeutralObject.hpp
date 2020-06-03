
#ifndef NeutralObject_hpp
#define NeutralObject_hpp

#include <stdio.h>
#include "../Object.hpp"
#include "../combatObject/CombatObject.hpp"


class NeutralObject : public Object
{
public:
    
    void eventHandler(Event *event) override;
    virtual v8::Local<v8::Object> getFullInfo();
};

#endif /* NeutralObject_hpp */