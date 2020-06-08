#ifndef OOP_DEFENSE_H
#define OOP_DEFENSE_H
#include "Attribute.h"

class Defense : public Attribute{
public:
    explicit Defense(int val) : Attribute(val) {};
};
#endif //OOP_DEFENSE_H
