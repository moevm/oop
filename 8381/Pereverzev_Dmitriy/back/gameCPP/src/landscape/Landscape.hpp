
#ifndef Landscape_hpp
#define Landscape_hpp

#include <stdio.h>
#include <string>

#include "../TypeСonstants.hpp"

class Landscape
{
public:
    
    virtual unsigned int getLandscapeType() = 0;
    virtual bool checkAccessMove(unsigned int objectType) = 0;
    virtual bool checkAccessInteraction(unsigned int objectType) = 0;
};

#endif /* Landscape_hpp */