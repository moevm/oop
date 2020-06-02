#ifndef IPRINTABLE_H
#define IPRINTABLE_H
#include <QString>

class printInterface
{
public:
    virtual QString getClass() = 0;
    virtual ~printInterface() = default;
};

#endif // IPRINTABLE_H
