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

    [[nodiscard]] bool meleeAttack(size_t x, size_t y) const override;
    void describeYourself() override;
    std::string getType() override;

    void magicFist() override;
    void healing() override;

    ~Demon() override;
};

#endif //OOP_DEMON_H
