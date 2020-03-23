#ifndef HEALLEROBJECT_H
#define HEALLEROBJECT_H

#include "NeutralObject/neutralobject.h"

#include "Strategy/heallerstrategy.h"

#include <qglobal.h>


class HeallerObject : public NeutralObject
{
public:
    HeallerObject();
    ~HeallerObject();

    char draw() override;

    HeallerObject* clone() override;

protected:
    void selectStrategy(Unit* unit) override;
};

#endif // HEALLEROBJECT_H
