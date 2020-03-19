#ifndef IFARMING_H
#define IFARMING_H

#include <cstddef>


constexpr size_t NO_GOLD = 0;
constexpr size_t ONE_GOLD = 1;
constexpr size_t FIVE_GOLD = 5;


class IFarming
{
public:
    virtual ~IFarming() = default;

    virtual size_t farm() const = 0;
};

#endif // IFARMING_H
