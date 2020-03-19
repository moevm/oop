#include "healerobject.h"

using namespace unit;


HealerObject::HealerObject(const HealerObject& object)
{
    if (object.strategy) {
        this->strategy = object.strategy->clone();
    }
}


HealerObject& HealerObject::operator=(const HealerObject& object)
{
    if (this == &object) {
        return *this;
    }

    if (object.strategy) {
        this->strategy = object.strategy->clone();
    }

    return *this;
}


std::shared_ptr<NeutralObject> HealerObject::clone() const
{
    return std::make_shared<HealerObject>(*this);
}


void HealerObject::selectStrategy(std::shared_ptr<Unit> unit)
{
    Q_UNUSED(unit);

    strategy = std::make_shared<HealerStrategy>();
}
