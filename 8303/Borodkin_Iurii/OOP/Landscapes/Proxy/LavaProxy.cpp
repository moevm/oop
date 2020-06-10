#include "LavaProxy.h"

LavaProxy::LavaProxy()
{
    lava = new Lava();
}

void LavaProxy::kill(Object *&unit)
{
    lava->kill(unit);
}

LavaProxy::~LavaProxy()
{
    delete lava;
}
