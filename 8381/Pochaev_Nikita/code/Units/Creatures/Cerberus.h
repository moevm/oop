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

    [[nodiscard]] bool meleeAttack(size_t x, size_t y) const override;
    void describeYourself() override;
    std::string getType() override;

    void postMortem() override;
    void armament() override;

    ~Cerberus() override;
};


#endif //OOP_CERBERUS_H
