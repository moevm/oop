#ifndef Mountain_hpp
#define Mountain_hpp

#include <stdio.h>
#include "../../Landscape.hpp"

class Mountain : public Landscape
{
public:
    unsigned int getLandscapeType() override;
    bool checkAccessMove(unsigned int objectType) override;
    bool checkAccessInteraction(unsigned int objectType) override;
};

#endif /* Mountain_hpp */