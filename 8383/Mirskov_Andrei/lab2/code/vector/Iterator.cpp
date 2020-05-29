//
// Created by andrei on 26.02.2020.
//

#include "Iterator.h"

template <class Type>
Iterator<Type>::Iterator(Type* elem) {
    this->elem = elem;
}

template<class Type>
Type Iterator<Type>::operator*() {
    return *this->elem;
}

template<class Type>
void Iterator<Type>::operator++() {
    this->elem++;
}

template<class Type>
bool Iterator<Type>::operator==(Iterator iterator) {
    return this->elem == iterator->elem;
}
