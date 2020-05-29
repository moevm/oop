//
// Created by andrei on 19.02.2020.
//

#ifndef OOP_LAB1_VECTOR_H
#define OOP_LAB1_VECTOR_H

#include <cstdlib>
#include "Iterator.h"
#include "Iterator.cpp"

template<class T>
class Vector {
public:
    explicit Vector(int elemCount = 0);

    void push(T elem);

    void remove(int ind);

    T &operator[](int i);

    int getSize();

    Iterator<T> begin();

    Iterator<T> end();

private:
    int size = 0;
    size_t elemSize = sizeof(T);
    T *data;
};


#endif //OOP_LAB1_VECTOR_H
