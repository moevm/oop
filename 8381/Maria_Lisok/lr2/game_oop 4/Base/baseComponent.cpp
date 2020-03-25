#include "Base/baseComponent.h"

BaseComponent *BaseComponent::getParent() const
{
    return parent;
}

void BaseComponent::setParent(BaseComponent *value)
{
    parent = value;
}

void BaseComponent::Add(BaseComponent *component)
{

}

void BaseComponent::Remove(BaseComponent *component)
{

}

bool BaseComponent::IsComposite() const
{
    return false;
}

#include "Base/baseComponent.h"
