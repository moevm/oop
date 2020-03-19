#ifndef HEALEROBJECT_H
#define HEALEROBJECT_H

#include "neutralobject.h"


class HealerObject : public NeutralObject
{
public:
    HealerObject() = default;
    HealerObject(const HealerObject& object);
    HealerObject& operator=(const HealerObject& object);

    virtual std::shared_ptr<NeutralObject> clone() const override;

protected:
    virtual void selectStrategy(std::shared_ptr<unit::Unit> unit) override;
};

#endif // HEALEROBJECT_H
