#ifndef NOOBJECT_H
#define NOOBJECT_H

#include "neutralobject.h"


class NoObject : public NeutralObject
{
public:
    NoObject() = default;
    NoObject(const NoObject& object);
    NoObject& operator=(const NoObject& object);

    virtual std::shared_ptr<NeutralObject> clone() const override;

    virtual char draw() const override;

protected:
    virtual void selectStrategy(std::shared_ptr<unit::Unit> unit) override;
};

#endif // NOOBJECT_H
