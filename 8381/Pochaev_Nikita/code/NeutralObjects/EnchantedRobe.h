#ifndef OOP_ENCHANTEDROBE_H
#define OOP_ENCHANTEDROBE_H

#include "NeutralObject.h"

class EnchantedRobe : public NeutralObject
{
public:
    ~EnchantedRobe() override = default;
    void operator+= (const std::shared_ptr<Unit> &unit) override;
    std::string getNameOfNeutralObject() override;
};

#endif //OOP_ENCHANTEDROBE_H
