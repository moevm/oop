#ifndef LANDSCAPELIBRARY_H
#define LANDSCAPELIBRARY_H

#include <map>
#include "game_elements/landscape/landscape.h"

class LandscapeLibrary
{
private:
    std::map<std::string, Landscape*> library;

public:
    ~LandscapeLibrary();
    void addLandscape(Landscape* landscape);
    const Landscape& getLandscape(const std::string &id) const;
};

#endif // LANDSCAPELIBRARY_H
