#ifndef FACADE_H
#define FACADE_H
//#include "Command.h"
#include "Field.h"
#include "ChainOfCommand.h"
#include "adapter.h"

class Facade
{
private:
    Field *field;
    chainOfResponsibility *basecomm;
    Adapter* adapter;
public:
    Facade() {
        adapter = new Adapter();
    }

    void createField();
    void play();

    ~Facade() {
        delete adapter;
    }

};

#endif // FACADE_H
