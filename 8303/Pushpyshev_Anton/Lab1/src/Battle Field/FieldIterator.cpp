#include "FieldIterator.h"

//написать геттеры и сеттеры
FieldIterator::FieldIterator(Field *field) : active(true), field(field), curWidth(0), curHeight(0){
    if (field->field[curWidth][curHeight].unit == nullptr)
        this->operator++();
}

bool FieldIterator::isActive()
{
    return active;
}

Cell *FieldIterator::operator->()
{
    return &field->field[curWidth][curHeight];
}

Cell *FieldIterator::operator++()
{
    do{
        if (curWidth + 1 == field->lengthX){
            if (curHeight + 1 == field->lengthY){
                active = false;
                return nullptr;
            }
            curWidth = 0;
            curHeight++;
        }
        else
            curWidth++;
    } while (field->field[curWidth][curHeight].unit == nullptr);
    return  &field->field[curWidth][curHeight];
}
#include "FieldIterator.h"
