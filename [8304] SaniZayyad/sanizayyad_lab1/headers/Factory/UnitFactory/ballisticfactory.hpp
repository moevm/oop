#ifndef ballisticfactory_hpp
#define ballisticfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

class BallisticFactory : public UnitFactory
{
public:
    explicit BallisticFactory() = default;
    virtual ~BallisticFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) override;

};


#endif /* ballisticfactory_hpp */
