#ifndef OOP_BAR_H
#define OOP_BAR_H
#include "NeutralObject.h"

class Bar : public NeutralObject{
public:
    Bar() {setName('B'); setObjName(BAR);};
};

#endif //OOP_BAR_H
