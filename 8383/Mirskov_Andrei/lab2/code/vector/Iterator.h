//
// Created by andrei on 26.02.2020.
//

#ifndef OOP_LAB1_ITERATOR_H
#define OOP_LAB1_ITERATOR_H

template <class Type>
class Iterator {
public:
    explicit Iterator(Type* elem);

    Type operator*();

    void operator++();

    bool operator==(Iterator iterator);

private:
    Type* elem;
};



#endif //OOP_LAB1_ITERATOR_H
