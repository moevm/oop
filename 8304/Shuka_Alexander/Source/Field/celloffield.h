#ifndef CELLOFFIELD_H
#define CELLOFFIELD_H

#include <memory>

#include "Unit/unit.h"

#include "Factory/ObjectFactory/noobjectfactory.h"

#include "Landscape/spikeslandscape.h"
#include "Landscape/proxylandscape.h"
#include "Landscape/roadlandscape.h"
#include "Landscape/foglandscape.h"


class CellOfField
{
public:
    explicit CellOfField();

    CellOfField(const CellOfField& cell);
    CellOfField(CellOfField&& cell);
    CellOfField& operator=(const CellOfField& cell);
    CellOfField& operator=(CellOfField&& cell);

    void addUnit(std::shared_ptr<unit::Unit> unit);
    void deleteUnit();
    std::shared_ptr<unit::Unit> getUnit() const;
    bool isEmpty() const;

    void setNeutralObject(std::shared_ptr<NeutralObject> neutralObject);
    std::shared_ptr<NeutralObject> getNeutralObject() const;
    void deleteNeutralObject();

    void setLandscape(std::shared_ptr<Landscape> landscape);
    std::shared_ptr<Landscape> getLandscape() const;

private:
    void doCopy(const CellOfField& cell);
    void doMove(CellOfField& cell);

private:
    std::shared_ptr<unit::Unit> unit;
    std::shared_ptr<NeutralObject> neutralObject;
    std::shared_ptr<Landscape> landscape;
    bool empty;
};

#endif // CELLOFFIELD_H
