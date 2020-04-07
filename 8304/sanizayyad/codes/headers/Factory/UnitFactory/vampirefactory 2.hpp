#ifndef vampirefactory_hpp
#define vampirefactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

class VampireFactory : public UnitFactory
{
public:
    explicit VampireFactory() = default;
    virtual ~VampireFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) override;

};


#endif /* vampirefactory_hpp */
