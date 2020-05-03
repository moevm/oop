#ifndef CELLOFGAMEFIELD_H
#define CELLOFGAMEFIELD_H

#include "Unit/unit.h"

#include "NeutralObject/neutralobject.h"

#include "Landscape/landscape.h"
#include "Landscape/proxylandscape.h"
#include "Landscape/foglandscape.h"
#include "Landscape/grasslanscape.h"
#include "Landscape/spineslandscape.h"

#include "NeutralObject/noobject.h"


class CellOfGameField
{
public:
    CellOfGameField();
    ~CellOfGameField() = default;

    CellOfGameField(const CellOfGameField& cell);
    CellOfGameField& operator=(CellOfGameField& cell);

    bool isEmpty();

    void addUnit(Unit* unit);
    void deleteUnit();
    Unit* getUnit();

    void addNeutralObject(NeutralObject* neutralObject);
    void deleteNeutralObject();
    NeutralObject* getNeutralObject();

    void addLandscape(Landscape* landscape);
    void deleteLandscape();
    Landscape* getlandscape();


protected:
    Unit* unit;
    NeutralObject* neutralObject;
    Landscape* landscape;

    bool empty;
};

#endif // CELLOFGAMEFIELD_H
