#include "dragonfactory.hpp"

std::shared_ptr<Unit> DragonFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator) const
{
     return std::make_shared<Dragon>(position,mediator);

}
