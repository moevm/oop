#include "Linker.h"
#include <QDebug>
void HeapUnit::add(const UnitPtr &unit)
{
    heap.push_back(unit);
}

void HeapUnit::remove(const UnitPtr &unit)
{
    heap.remove(unit);
}

Unit* HeapUnit::extractUnit()
{
    if (heap.empty()) return nullptr;
    auto unit = heap.front();
    heap.pop_front();

    return unit;
}

size_t HeapUnit::size() const
{
    return heap.size();
}

bool HeapUnit::empty() const
{
    return heap.empty();
}

const std::list <const HeapUnit::UnitPtr> HeapUnit::getUnits() const
{
    std::list <const HeapUnit::UnitPtr> constHeap;

    for (auto unitPtr : heap)
        constHeap.push_back(const_cast<const UnitPtr>(unitPtr));

    return constHeap;
}

HeapUnit::~HeapUnit()
{
    for (auto unitPtr : heap)
        delete unitPtr;

    heap.clear();
}
