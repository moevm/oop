#ifndef PROXY_H
#define PROXY_H
#include "Objects/Object.h"

class IProxy
{
public:
    virtual void kill(Object*&) = 0;
    virtual ~IProxy() = default;
};
#endif // PROXY_H
