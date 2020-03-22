#ifndef OOP_SWORDSMAN_H
#define OOP_SWORDSMAN_H

#include "../Unit.h"
#include "../IInfantry.h"

class Swordsman : public Unit, public IInfantry
{
public:
    Swordsman();
    Swordsman* clone() const override;

    explicit Swordsman(std::string inputName);

    [[nodiscard]] bool meleeAttack(size_t x, size_t y) const override;
    void describeYourself() override;
    std::string getType() override;

    void closeTheRanks() override;
    void fury() override;

    ~Swordsman() override;
};

#endif //OOP_SWORDSMAN_H
