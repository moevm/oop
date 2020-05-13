//
// Created by kot on 10.05.2020.
//

#ifndef CONTEXT_H
#define CONTEXT_H
#include "neutralObj.h"

class Context {
private:
    NeutralObj* obj;
public:
    Context(NeutralObj* obj = nullptr) : obj(obj) {}
    ~Context() {delete obj;}
    void setObject(NeutralObj* obj)
    {
        delete  this->obj;
        this->obj = obj;
    }
    void operator += (Unit& unit)
    {
        obj->operator+=(unit);
    }
};


#endif //CONTEXT_H
