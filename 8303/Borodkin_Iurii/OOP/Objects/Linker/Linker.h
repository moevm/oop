#ifndef LINKER_H
#define LINKER_H
#include <memory>
#include <list>

class Unit;

class IUnit
{
public:

    typedef Unit* UnitPtr;

    virtual void add(const UnitPtr&) = 0;

    virtual void remove(const UnitPtr&) = 0;

    virtual ~IUnit() = default;
};

class HeapUnit : public IUnit
{
public:
    void add(const UnitPtr&) override;

    void remove(const UnitPtr&) override;

    UnitPtr extractUnit();

    size_t size() const;

    bool empty() const;

    const std::list <const UnitPtr> getUnits() const;

    ~HeapUnit() override;

private:
    std::list<UnitPtr> heap;
};

#endif // LINKER_H
