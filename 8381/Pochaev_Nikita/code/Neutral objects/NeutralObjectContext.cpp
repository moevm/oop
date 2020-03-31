#include "NeutralObjectContext.h"

#include <utility>

NeutralObjectContext::NeutralObjectContext(std::shared_ptr<NeutralObject> &object_) : object(std::move(object_)) { }

void NeutralObjectContext::setObject(std::shared_ptr<NeutralObject> object_)
{
    object = std::move(object_);
}

void NeutralObjectContext::operator+=(const std::shared_ptr<Unit> &unit)
{
    object->operator+=(unit);
}
