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

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void closeTheRanks() override;
    void fury() override;

    ~Swordsman() override;
};

#endif //OOP_SWORDSMAN_H
