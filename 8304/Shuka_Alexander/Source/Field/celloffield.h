#ifndef CELLOFFIELD_H
#define CELLOFFIELD_H

#include <memory>

#include "Unit/unit.h"


class CellOfField
{
public:
    explicit CellOfField();
    ~CellOfField() = default;

    CellOfField(const CellOfField& cell);
    CellOfField(CellOfField&& cell);
    CellOfField& operator=(const CellOfField& cell);
    CellOfField& operator=(CellOfField&& cell);

    void addUnit(std::shared_ptr<Unit> unit);

    void deleteUnit();

    std::shared_ptr<Unit>& getUnit();

    bool isEmpty() const;

public:
    std::shared_ptr<Unit> unit;
    bool empty;
};

#endif // CELLOFFIELD_H
