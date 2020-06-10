#ifndef PACK_H
#define PACK_H
#include "Objects/Attributes.h"
#include <string>

class Pack
{
public:
    virtual Attributes buff();
    virtual std::string type();
    virtual ~Pack() = default;
};

#endif // PACK_H
