#ifndef OOP_UNITMEDIATORS_H
#define OOP_UNITMEDIATORS_H

#include <cstddef>
#include <memory>

class IGameField;
class Unit;

class UnitMediator
{
public:
    UnitMediator(std::shared_ptr<IGameField> field_, std::shared_ptr<Unit> unit_);
    virtual void connectWithUnit() = 0;
    virtual void Notify(std::shared_ptr<Unit> sender, size_t x, size_t y) = 0;
protected:
    std::shared_ptr<IGameField> field;
    std::shared_ptr<Unit> unit;
};

class UnitMoveMediator : public UnitMediator, public std::enable_shared_from_this<UnitMoveMediator>
{
public:
    UnitMoveMediator(std::shared_ptr<IGameField> field_, std::shared_ptr<Unit> unit_);
    void connectWithUnit() override;
    void Notify(std::shared_ptr<Unit> sender, size_t x, size_t y) override;
};

class UnitMeleeAttackMediator : public UnitMediator, public std::enable_shared_from_this<UnitMeleeAttackMediator>
{
public:
    UnitMeleeAttackMediator(std::shared_ptr<IGameField> field_, std::shared_ptr<Unit> unit_);
    void connectWithUnit() override;
    void Notify(std::shared_ptr<Unit> sender, size_t x, size_t y) override;
};

#endif //OOP_UNITMEDIATORS_H
