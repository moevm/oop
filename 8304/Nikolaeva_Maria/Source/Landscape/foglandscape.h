#ifndef FOGLANDSCAPE_H
#define FOGLANDSCAPE_H

#include "Landscape/landscape.h"

#include "qglobal.h"


class FogLandscape : public Landscape
{
public:
    void hurtUnit(Unit* unit) override;
    bool canMove(Unit* unit) override;
    Landscape* clone() override;

    char draw() override;

};

#endif // FOGLANDSCAPE_H
