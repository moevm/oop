#ifndef NOOBJECT_H
#define NOOBJECT_H

#include "NeutralObject/neutralobject.h"

#include "Strategy/nostrategy.h"

#include <qglobal.h>


class NoObject : public NeutralObject
{
public:
    NoObject();
    ~NoObject();

    char draw() override;

    NoObject* clone() override;

protected:
    void selectStrategy(Unit* unit) override;
};

#endif // NOOBJECT_H
