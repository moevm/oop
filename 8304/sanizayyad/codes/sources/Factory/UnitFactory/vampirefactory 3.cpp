#include "vampirefactory.hpp"

std::shared_ptr<Unit> VampireFactory::createUnit(const Position2D& position,
                                                 std::shared_ptr<Mediator> mediator) const
{
    return std::make_shared<Vampire>(position,mediator);

}
