#ifndef SPINESLANDSCAPE_H
#define SPINESLANDSCAPE_H

#include "Landscape/landscape.h"

#include "qglobal.h"


class SpinesLandscape : public Landscape
{
public:
    void hurtUnit(Unit* unit) override;
    bool canMove(Unit* unit) override;
    Landscape* clone() override;

    char draw() override;
};

#endif // SPINESLANDSCAPE_H
