#ifndef OOP_TRAININGBASE_H
#define OOP_TRAININGBASE_H
#include "NeutralObject.h"

class TrainingBase : public NeutralObject{
public:
    TrainingBase(){setName('T'); setObjName(TRAIN);};
};

#endif //OOP_TRAININGBASE_H
