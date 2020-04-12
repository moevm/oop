#ifndef OOP_DEMON_H
#define OOP_DEMON_H

#include "../Unit.h"
#include "../IWizard.h"

class Demon : public Unit, public IWizard
{
public:
    Demon();
    Demon* clone() const override;
    explicit Demon(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void magicFist() override;
    void healing() override;

    ~Demon() override;
};

#endif //OOP_DEMON_H
