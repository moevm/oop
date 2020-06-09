#ifndef OOP_ATTACK_H
#define OOP_ATTACK_H
#include "Attribute.h"

class Attack : public Attribute {
public:
    explicit Attack(int val) : Attribute(val) {};
};
#endif //OOP_ATTACK_H
