#ifndef Swamp_hpp
#define Swamp_hpp

#include <stdio.h>
#include "../../Landscape.hpp"

class Swamp : public Landscape
{
public:
    unsigned int getLandscapeType() override;
    bool checkAccessMove(unsigned int objectType) override;
    bool checkAccessInteraction(unsigned int objectType) override;
};

#endif /* Swamp_hpp */