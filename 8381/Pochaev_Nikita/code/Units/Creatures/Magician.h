#ifndef OOP_MAGICIAN_H
#define OOP_MAGICIAN_H

#include "../Unit.h"
#include "../IWizard.h"

class Magician : public Unit, public IWizard
{
public:
    Magician();
    Magician* clone() const override;

    explicit Magician(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void magicFist() override;
    void healing() override;

    ~Magician() override;
};


#endif //OOP_MAGICIAN_H
