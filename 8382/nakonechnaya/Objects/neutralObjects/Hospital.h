#ifndef OOP_HOSPITAL_H
#define OOP_HOSPITAL_H
#include "NeutralObject.h"

class Hospital : public NeutralObject{
public:
    Hospital() {setName('H'); setObjName(HOSPITAL);};
};
#endif //OOP_HOSPITAL_H
