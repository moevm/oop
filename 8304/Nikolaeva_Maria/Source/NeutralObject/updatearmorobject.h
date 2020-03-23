#ifndef UPDATEARMOROBJECT_H
#define UPDATEARMOROBJECT_H

#include "NeutralObject/neutralobject.h"

#include "Strategy/updateheavyarmorstrategy.h"
#include "Strategy/updatelightarmorstrategy.h"
#include "Strategy/updatenoarmorstrategy.h"

#include "Unit/archer.h"
#include "Unit/dragon.h"
#include "Unit/dwarf.h"
#include "Unit/harpy.h"
#include "Unit/liveshield.h"
#include "Unit/swordsman.h"

#include <qglobal.h>


class UpdateArmorObject : public NeutralObject
{
public:
    UpdateArmorObject();
    ~UpdateArmorObject();

    char draw() override;

    UpdateArmorObject* clone() override;

protected:
    void selectStrategy(Unit* unit) override;
};

#endif // UPDATEARMOROBJECT_H
