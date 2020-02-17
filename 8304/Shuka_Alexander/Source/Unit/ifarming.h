#ifndef IFARMING_H
#define IFARMING_H

#include <cstddef>

constexpr size_t NO_GOLD = 0;
constexpr size_t ONE_GOLD = 0;
constexpr size_t FIVE_GOLD = 0;


class IFarming
{
public:
    virtual ~IFarming() = default;

    virtual size_t farm() = 0;
};

#endif // IFARMING_H
