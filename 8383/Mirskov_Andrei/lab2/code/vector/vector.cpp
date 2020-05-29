//
// Created by andrei on 19.02.2020.
//

#include "vector.h"

template <class T>
Vector<T>::Vector(int elemCount) {
    this->data = (T *) malloc(this->elemSize * (elemCount + 1));
    this->size = elemCount;
}

template<class T>
void Vector<T>::push(T elem) {
    this->data = (T *) realloc(this->data, this->elemSize * (this->size + 1));
    this->data[this->size] = elem;
    this->size++;
}

template<class T>
void Vector<T>::remove(int ind) {
    this->size--;
    for (int i = ind; i < this->size; i++) {
        this->data[i] = this->data[i + 1];
    }
}

template<class T>
T& Vector<T>::operator[](int i) {
    return this->data[i];
}

template<class T>
int Vector<T>::Vector::getSize() {
    return this->size;
}

template<class T>
Iterator<T> Vector<T>::begin() {
    return Iterator<T>(this->data);
}

template<class T>
Iterator<T> Vector<T>::end() {
    return Iterator<T>(this->data + this->getSize());
}
