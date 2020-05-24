#ifndef swordmanfactory_hpp
#define swordmanfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

class SwordManFactory : public UnitFactory
{
public:
    explicit SwordManFactory() = default;
    virtual ~SwordManFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) override;

};

#endif /* swordmanfactory_hpp */
