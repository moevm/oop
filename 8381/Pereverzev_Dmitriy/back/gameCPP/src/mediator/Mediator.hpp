

#ifndef Mediator_hpp
#define Mediator_hpp

#include <stdio.h>
#include <iostream>


class Field;
class Mediator
{
public:
    virtual void interactionObjObj(Field *field, unsigned int fromRowNumber, unsigned int fromColumnNumber, unsigned int toRowNumber, unsigned int toColumnNumber) = 0;
};

#endif /* Mediator_hpp */
