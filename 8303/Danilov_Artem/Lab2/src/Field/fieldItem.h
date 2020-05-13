#ifndef FIELDITEM_H
#define FIELDITEM_H

#include "../NeutralObject/neutralObj.h"
#include "../Landscape/landscape.h"

class FieldItem
{
public:
    FieldItem();
    FieldItem(const FieldItem&);
    FieldItem(FieldItem&&);
    ~FieldItem();
    FieldItem& operator = (const FieldItem&);
    FieldItem& operator = (FieldItem&&);
    void addUnit(Unit*);
    void delUnit();
    void addNeutral(NeutralObj*);
    void delNeutral();
    void setLandscape(Landscape*);
    void delLandscape();
    bool isUnitFree() const;
    Unit* getUnit() const;
    NeutralObj* getNeutral() const;
    Landscape* getLandscape() const;
//    std::string characteristics(unsigned, unsigned);
//    virtual bool isMovable() = 0;
//    virtual std::string about() = 0;
//    virtual std::string shortName() = 0;
//    virtual FieldItem* itemCopy() = 0;
//    virtual void move(int x, int y) = 0;
//    virtual void setMoveMediator(MoveMediator *value) = 0;
private:
    Unit* unit;
    NeutralObj* neutral;
    Landscape* land;
};

#endif //FIELDITEM_H
