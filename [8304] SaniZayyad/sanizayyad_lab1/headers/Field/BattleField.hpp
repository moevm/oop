#ifndef BattleField_hpp
#define BattleField_hpp

#include "FieldCell.hpp"

#include <stdio.h>
#include <memory>

class BattleFieldIterator;

class BattleField
{
    friend BattleFieldIterator;
public:
    explicit BattleField(size_t height, size_t width);
    virtual ~BattleField() = default;

    BattleField(const BattleField& BattleField);
    BattleField& operator=(const BattleField& BattleField);
    BattleField(BattleField&& BattleField);
    BattleField& operator=(BattleField&& BattleField);

    size_t getWidth() const;
    size_t getHeight() const;
    size_t getNumberOfUnits() const;

    bool addUnit(std::shared_ptr<Unit> unit);
    void deleteUnit(std::shared_ptr<Unit> unit);
    void deleteUnitCord(Position2D position);

    FieldCell& getFieldCell(const Position2D& position);
    void getFieldCellInfo(const Position2D &position);

    

private:
    size_t numberOfUnits;
    size_t height;
    size_t width;
    std::unique_ptr<std::unique_ptr<FieldCell[]>[]> battleFieldArray;
};

#endif /* BattleField_hpp */
