#ifndef KILLEROBJECT_H
#define KILLEROBJECT_H

#include "NeutralObject/neutralobject.h"

#include "Strategy/killerstrategy.h"

#include <qglobal.h>


class KillerObject : public NeutralObject
{
public:
    KillerObject();
    ~KillerObject();

    char draw() override;

    KillerObject* clone() override;

protected:
    void selectStrategy(Unit* unit) override;
};

#endif // KILLEROBJECT_H
