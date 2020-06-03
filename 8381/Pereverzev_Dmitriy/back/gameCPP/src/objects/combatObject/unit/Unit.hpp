
#ifndef Unit_hpp
#define Unit_hpp

#include <stdio.h>
#include "../CombatObject.hpp"



class Unit : public CombatObject
{
protected:
    void death() override;

public:
    ~Unit();
    
    
    
    
    
    
    
    bool isMoveable() override;
    void operator+(Object *object) override;

    
    v8::Local<v8::Object> getFullInfo() override;

    void eventHandler(Event *event) override;
};

#endif /* Unit_hpp */
