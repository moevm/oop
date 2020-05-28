#ifndef MYLITTLEGAME_LANDSCAPE_H
#define MYLITTLEGAME_LANDSCAPE_H
#include "UnitFactory.h"
#endif //MYLITTLEGAME_LANDSCAPE_H

struct Landscape{
    virtual void execute(std::unique_ptr<Unit> & unit) = 0;
};


struct Grass : Landscape{
    void execute(std::unique_ptr<Unit> & unit);
};

struct Mount : Landscape{
    void execute(std::unique_ptr<Unit> & unit);
};

struct Dust : Landscape{
    void execute(std::unique_ptr<Unit> & unit);
};


struct ProxyLandscape : Landscape{
    ProxyLandscape(LandscapeTypes type);
    std::shared_ptr<Landscape> landscape;
    void execute(std::unique_ptr<Unit> & unit);
};