#include "archerfactory.hpp"

std::shared_ptr<Unit> ArcherFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator) const
{
     return std::make_shared<Archer>(position,mediator);

}
