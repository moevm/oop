#ifndef archerfactory_hpp
#define archerfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

class ArcherFactory : public UnitFactory
{
public:
    explicit ArcherFactory() = default;
    virtual ~ArcherFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) override;

};

#endif /* archerfactory_hpp */
