#ifndef OOP_IFRIT_H
#define OOP_IFRIT_H

#include "../Unit.h"
#include "../IInfantry.h"

class Ifrit : public Unit, public IInfantry
{
public:
    Ifrit();
    Ifrit* clone() const override;

    explicit Ifrit(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void closeTheRanks() override;
    void fury() override;

    ~Ifrit() override;
};

#endif //OOP_IFRIT_H
