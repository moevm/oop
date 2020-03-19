#include "noobject.h"

using namespace unit;


NoObject::NoObject(const NoObject& object)
{
    if (object.strategy) {
        this->strategy = object.strategy->clone();
    }
}


NoObject& NoObject::operator=(const NoObject& object)
{
    if (this == &object) {
        return *this;
    }

    if (object.strategy) {
        this->strategy = object.strategy->clone();
    }

    return *this;
}


std::shared_ptr<NeutralObject> NoObject::clone() const
{
    return std::make_shared<NoObject>(*this);

}


char NoObject::draw() const
{
    return '.';
}


void NoObject::selectStrategy(std::shared_ptr<Unit> unit)
{
    Q_UNUSED(unit);

    strategy = std::make_shared<NoStrategy>();
}
