#ifndef LAVAPROXY_H
#define LAVAPROXY_H
#include "../Lava.h"

class LavaProxy : IProxy
{
public:
    LavaProxy();
    void kill(Object *&) override;
    ~LavaProxy() override;
private:
    IProxy *lava;
};

#endif // LAVAPROXY_H
