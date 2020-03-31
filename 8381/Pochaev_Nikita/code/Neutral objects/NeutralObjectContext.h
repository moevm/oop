#ifndef OOP_NEUTRALOBJECTCONTEXT_H
#define OOP_NEUTRALOBJECTCONTEXT_H

#include "NeutralObject.h"

class NeutralObjectContext
{
private:
    std::shared_ptr<NeutralObject> object{};
public:
    NeutralObjectContext() = default;
    explicit NeutralObjectContext(std::shared_ptr<NeutralObject> &object_);
    ~NeutralObjectContext() = default;
    void setObject(std::shared_ptr<NeutralObject> object_);
    void operator+= (const std::shared_ptr<Unit> &unit);
};

#endif //OOP_NEUTRALOBJECTCONTEXT_H
