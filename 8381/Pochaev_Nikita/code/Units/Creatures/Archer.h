#ifndef OOP_ARCHER_H
#define OOP_ARCHER_H

#include "../Unit.h"
#include "../IShooter.h"

class Archer : public Unit, public IShooter
{
public:
    Archer();
    Archer* clone() const override;
    explicit Archer(std::string inputName);

    [[nodiscard]] bool meleeAttack(size_t x, size_t y) const override;
    void describeYourself() override;
    std::string getType() override;

    void shot() override;
    void canopyShooting() override;

    ~Archer() override;
};

#endif //OOP_ARCHER_H
