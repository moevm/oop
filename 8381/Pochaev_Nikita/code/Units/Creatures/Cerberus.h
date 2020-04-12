#ifndef OOP_CERBERUS_H
#define OOP_CERBERUS_H

#include "../Unit.h"
#include "../ICavalry.h"

class Cerberus : public Unit, public ICavalry
{
public:
    Cerberus();
    Cerberus* clone() const override;
    explicit Cerberus(std::string inputName);

    void describeYourself() override;
    std::string getUnitInf() override;
    eUnitsType getType() override;

    void postMortem() override;
    void armament() override;

    ~Cerberus() override;
};


#endif //OOP_CERBERUS_H
