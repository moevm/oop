#ifndef OOP_HEALTH_H
#define OOP_HEALTH_H
#include "Attribute.h"

class Health : public Attribute{
public:
    explicit Health(int val) : Attribute(val) {};
};
#endif //OOP_HEALTH_H
