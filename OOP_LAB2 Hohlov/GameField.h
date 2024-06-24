#ifndef OOP_LAB1_GAMEFIELD_H
#define OOP_LAB1_GAMEFIELD_H

#include "Point.h"
#include "GameObject.h"
#include "GameFieldIterator.h"
#include "FieldCell.h"
#include "UnitObserver.h"
#include "BaseObserver.h"
#include "VikingsStrategy.h"
#include "ArcherStrategy.h"
#include "WizardStrategy.h"
#include "Base.h"
#include "NeutralObject.h"
#include "Unit.h"

#include <iostream>

class GameField: public UnitObserver, public BaseObserver {

private:

    FieldCell **field;

    int fieldHeight;
    int fieldWidth;

public:

    GameField();
    explicit GameField(int fieldSize);
    GameField(int fieldHeight, int fieldWidth);
    ~GameField();

    void deleteObject(int x, int y);
    void deleteObject(const Point &point);
    void deleteObject(GameObject *object);

    void addObject(GameObject *object, int x, int y);
    void addObject(GameObject *object, Point p);

    void moveObject(const Point &p1, const Point &p2);
    void moveObject(GameObject *object, const Point &p2);

    int getHeight() const;
    int getWidth() const;
    FieldCell *getCell(const Point &p) const;

    friend std::ostream& operator<< (std::ostream &stream, const GameField &field);

    GameFieldIterator begin(){ return GameFieldIterator(Point(0, 0), field, fieldHeight, fieldWidth); }
    GameFieldIterator end(){ return GameFieldIterator(Point(0, fieldHeight), field, fieldHeight, fieldWidth); }

    void onUnitAttack(Unit *unit, Unit *other) override;
    void onUnitMove(Unit *unit, Point p) override;
    void onUnitDestroy(Unit *unit) override;
    void onUnitDamaged(Unit *unit) override {}
    void onUnitHeal(Unit *unit) override {}

    void onBaseNewUnitCreated(Unit *unit, Point position) override;

    void addBase(Base *base, Point position);
    void addBase(Base *base, int x, int y);

};

#endif //OOP_LAB1_GAMEFIELD_H