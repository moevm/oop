
#ifndef LandscapeProxy_hpp
#define LandscapeProxy_hpp

#include <stdio.h>
#include <iostream>
#include "../Landscape.hpp"
#include "../varietyLandscapes/forest/Forest.hpp"
#include "../varietyLandscapes/mountain/Mountain.hpp"
#include "../varietyLandscapes/plain/Plain.hpp"
#include "../varietyLandscapes/swamp/Swamp.hpp"

class LandscapeProxy : public Landscape
{
private:
    Landscape *landscape;

public:
    LandscapeProxy();
    LandscapeProxy(unsigned int landscapeType);
    ~LandscapeProxy();
    unsigned int getLandscapeType() override;
    bool checkAccessMove(unsigned int objectType) override;
    bool checkAccessInteraction(unsigned int objectType) override;
};

#endif /* LandscapeProxy_hpp */