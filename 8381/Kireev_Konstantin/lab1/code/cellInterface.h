#ifndef CELLINTERFACE_H
#define CELLINTERFACE_H
#include <printInterface.h>

class cellInterface : public printInterface
{
public:
    virtual ~cellInterface() = default; //деструктор
    virtual bool isMove() const = 0; //подвижен ли объект
    virtual cellInterface* copy() = 0; //копирование объекта на поле
};

#endif // CELLINTERFACE_H
