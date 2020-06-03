
#ifndef Plain_hpp
#define Plain_hpp

#include <stdio.h>
#include "../../Landscape.hpp"

class Plain : public Landscape
{
public:
    unsigned int getLandscapeType() override;
    bool checkAccessMove(unsigned int objectType) override;
    bool checkAccessInteraction(unsigned int objectType) override;
};

#endif /* Plain_hpp */