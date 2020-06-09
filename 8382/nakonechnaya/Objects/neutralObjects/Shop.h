#ifndef OOP_SHOP_H
#define OOP_SHOP_H
#include "NeutralObject.h"

class Shop : public NeutralObject{
public:
    Shop(){setName('S'); setObjName(SHOP);};
};

#endif //OOP_SHOP_H
