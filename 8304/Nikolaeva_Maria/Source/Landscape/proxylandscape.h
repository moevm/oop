#ifndef PROXYLANDSCAPE_H
#define PROXYLANDSCAPE_H

#include "Landscape/landscape.h"
#include "Landscape/grasslanscape.h"


class ProxyLandscape : public Landscape
{
public:
    explicit ProxyLandscape();
    explicit ProxyLandscape(Landscape* landscape);

    void hurtUnit(Unit* unit) override;
    bool canMove(Unit* unit) override;
    Landscape* clone() override;

    char draw() override;

private:
    Landscape* landscape;
};


#endif // PROXYLANDSCAPE_H
