#ifndef FOREST_H
#define FOREST_H
#include "landscape.h"
class Forest: public Landscape{
public:
    string getLandscapeType();
    bool canStand();
};
#endif // FOREST_H
