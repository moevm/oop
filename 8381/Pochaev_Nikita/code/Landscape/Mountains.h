#ifndef OOP_MOUNTAINS_H
#define OOP_MOUNTAINS_H

#include "Landscape.h"

class Mountains : public Landscape
{
public:
    Mountains();
    std::string getNameOfLandscape();
};

#endif //OOP_MOUNTAINS_H
