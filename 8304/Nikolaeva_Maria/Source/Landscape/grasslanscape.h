#ifndef GRASSLANSCAPE_H
#define GRASSLANSCAPE_H

#include "Landscape/landscape.h"

#include "qglobal.h"


class GrassLanscape : public Landscape
{
public:
    void hurtUnit(Unit* unit) override;
    bool canMove(Unit* unit) override;
    Landscape* clone() override;

    char draw() override;
};

#endif // GRASSLANSCAPE_H

