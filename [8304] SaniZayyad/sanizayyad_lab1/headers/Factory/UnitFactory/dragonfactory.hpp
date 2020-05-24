#ifndef dragonfactory_hpp
#define dragonfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

class DragonFactory : public UnitFactory
{
public:
    explicit DragonFactory() = default;
    virtual ~DragonFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) override;

};

#endif /* dragonfactory_hpp */
