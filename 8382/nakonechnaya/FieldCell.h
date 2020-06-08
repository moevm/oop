#ifndef OOP_FIELDCELL_H
#define OOP_FIELDCELL_H
#include "landscapes/Forest.h"
#include "landscapes/Grass.h"
#include "landscapes/Mountains.h"
#include "landscapes/Swamp.h"
#include "landscapes/Proxy.h"

#include "Objects/units/FootTroops/Halberdier.h"
#include "Objects/units/FootTroops/Skeleton.h"
#include "Objects/units/RangedTroops/Archer.h"
#include "Objects/units/RangedTroops/Lich.h"
#include "Objects/units/FlyingTroops/Griffin.h"
#include "Objects/units/FlyingTroops/BoneDragon.h"

#include "Objects/neutralObjects/Bar.h"
#include "Objects/neutralObjects/Hospital.h"
#include "Objects/neutralObjects/Shop.h"
#include "Objects/neutralObjects/TrainingBase.h"

class FieldCell {
public:
    explicit FieldCell();
    explicit FieldCell(int land, int obj, bool base, Unit *unit1);
    bool isEmpty() { return unit == nullptr; };
    bool isObject() { return object != nullptr; };
    void setUnit(Unit *unit1) {this->unit = unit1;};
    Unit *getUnit() {return unit;};
    void setBase() {base = true;};
    bool isBase() {return base;};
    void setCoordinates(int x, int y);
    Coordinates *getCoordinates() {return coordinates;};
    NeutralObject *getObject() {return object;};
    void deleteUnit(int flag=0) {if (!flag) {delete unit;}; unit = nullptr;}; // если перемещение, то просто nullptr
    Landscape *getLandscape() { return landscape;};
    void deleteObject(){delete object; object = nullptr;};
    void setLandscape(int land);
    void setObject(int obj);
    void deleteBase(){base = false;};
private:
    Unit *unit;
    Landscape *landscape;
    NeutralObject *object;
    bool base;
    Coordinates *coordinates;
};
#endif //OOP_FIELDCELL_H
