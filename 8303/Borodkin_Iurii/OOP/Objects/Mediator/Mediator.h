#ifndef MEDIATOR_H
#define MEDIATOR_H

class Object;
class Mediator
{
public:
    virtual void attack(Object*) const = 0;
    virtual ~Mediator() = default;
};

#endif // MEDIATOR_H
