#ifndef OOP_COMPOSITEUNIT_H
#define OOP_COMPOSITEUNIT_H

#include <vector>
#include <memory>
#include "Unit.h"
#include "InformationHeaders/constPar.h"

class CompositeUnit : public Unit
{
public:
    CompositeUnit() = default;
    ~CompositeUnit() override = default;
    [[nodiscard]] Unit* clone() const override;
    void initCurrPar();
    void addUnit(std::shared_ptr<Unit> unit) override;
    [[nodiscard]] size_t getHealth() const override;
    [[nodiscard]] size_t getArmor() const override;
    [[nodiscard]] size_t getMeleeAttackStrength() const override;
    [[nodiscard]] size_t getUnitQuantity() const override;
    void setMeleeAttackBoost(size_t boost) override;
    void setArmorBoost(size_t boost) override;

    [[nodiscard]] CompositeUnit* isComposite() override;
    [[nodiscard]] eUnitsType getType() override;
    [[nodiscard]] std::map<eUnitsType, size_t> getComposition() override;
    void reallocation(size_t new_x, size_t new_y) override;

    void takeDamage(size_t damageSize) override;
    void describeYourself() override;
    std::string getUnitInf() override;

private:
    std::vector<std::shared_ptr<Unit>> units;
};

#endif //OOP_COMPOSITEUNIT_H
