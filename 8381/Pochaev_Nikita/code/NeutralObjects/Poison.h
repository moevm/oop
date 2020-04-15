#ifndef OOP_POISON_H
#define OOP_POISON_H

#include "NeutralObject.h"

class Poison : public NeutralObject
{
public:
    ~Poison() override = default;
    void operator+= (const std::shared_ptr<Unit> &unit) override;
    std::string getNameOfNeutralObject() override;
};

#endif //OOP_POISON_H
