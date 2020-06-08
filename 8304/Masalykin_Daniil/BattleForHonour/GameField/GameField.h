#ifndef BATTLEFORHONOUR_GAMEFIELD_H
#define BATTLEFORHONOUR_GAMEFIELD_H


#include "Point.h"
#include "GameFieldIterator.h"
#include "FieldCell.h"
#include "../Objects/Neutrals/InfantryStrategy.h"
#include "../Objects/Neutrals/ArcherStrategy.h"
#include "../Objects/Neutrals/DruidStrategy.h"
#include "../Objects/Base.h"
#include <iostream>

class GameField: public UnitObserver, public BaseObserver {

private:

    FieldCell **field;

    int fieldHeight;
    int fieldWidth;

public:

    GameField();
    GameField(int fieldHeight, int fieldWidth);
    ~GameField();
    void reset();

    void deleteObject(int x, int y);
    void deleteObject(const Point &point);
    void deleteObject(GameObject *object);

    bool addObject(GameObject *object, int x, int y);
    bool addObject(GameObject *object, Point p);

    void moveObject(const Point &p1, const Point &p2);
    void setBorders();

    [[nodiscard]] FieldCell *getCell(const Point &p) const;
    FieldCell *getCell(const int x, const int y);

    friend std::ostream& operator<< (std::ostream &stream, const GameField &field);

    GameFieldIterator begin(){ return GameFieldIterator(Point(0, 0), field, fieldHeight, fieldWidth); }
    GameFieldIterator end(){ return GameFieldIterator(Point(0, fieldHeight), field, fieldHeight, fieldWidth); }

    void onUnitAttack(Unit *unit, Unit *enemy) override;
    void onUnitMove(Unit *unit, Point p) override;
    void onUnitDestroy(Unit *unit) override;
    void onUnitDamaged(Unit *unit) override {}
    void onUnitHeal(Unit *unit) override {}

    void onBaseNewUnit(Unit *unit, Point pos) override;
    bool addBase(Base *base, Point pos);
    bool addBase(Base *base, int x, int y);

    [[nodiscard]] bool checkBorder(const Point &p) const;

};

#endif //BATTLEFORHONOUR_GAMEFIELD_H
