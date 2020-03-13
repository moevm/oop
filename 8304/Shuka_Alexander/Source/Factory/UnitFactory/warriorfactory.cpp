#include "warriorfactory.h"

using namespace unit;


std::shared_ptr<Unit>
WarriorFactory::createUnit(const Point2D& point,
                           std::shared_ptr<Mediator> mediator) const
{
    return std::make_shared<Warrior>(point, mediator);
}
