
#ifndef Forest_hpp
#define Forest_hpp

#include <stdio.h>
#include "../../Landscape.hpp"

class Forest : public Landscape
{
public:
    unsigned int getLandscapeType() override;
    bool checkAccessMove(unsigned int objectType) override;
    bool checkAccessInteraction(unsigned int objectType) override;
};

#endif /* Forest_hpp */