#ifndef spearmanfactory_hpp
#define spearmanfactory_hpp

#include "unitfactory.hpp"

#include <stdio.h>

class SpearManFactory : public UnitFactory
{
public:
    explicit SpearManFactory() = default;
    virtual ~SpearManFactory() = default;

    virtual std::shared_ptr<Unit> createUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) override;

};

#endif /* spearmanfactory_hpp */
