#include <stdexcept>
#include <iostream>

#include "objectcontainer.h"

ObjectContainer::ObjectContainer():
    iSize(0), iUsed(0), objects(nullptr)
{}


ObjectContainer::~ObjectContainer()
{
    delete [] objects;
}


void ObjectContainer::erase()
{
    delete [] objects;
    iSize = 0;
    iUsed = 0;
    objects = nullptr;
}


Object* ObjectContainer::operator[](int index) const
{
    if(index >= 0 && unsigned(index) < iUsed)
        return objects[index];
    throw std::range_error("Nonexistent item");
}


unsigned int ObjectContainer::length() const
{
    return iUsed;
}


void ObjectContainer::resize(int iNewSize){
    if(iSize == unsigned(iNewSize))
        return;

    if(iNewSize <= 0)
    {
        erase();
        return;
    }

    Object **new_array = new Object*[static_cast<unsigned int>(iNewSize)];

    if(iSize > 0)
    {
        int iToCopySize = (int(iSize) > iNewSize) ? iNewSize : int(iSize);

        for(int index = 0; index < iToCopySize; index++)
        {
            new_array[index] = objects[index];
        }
    }

    delete [] objects;

    objects = new_array;
    iSize = unsigned(iNewSize);
}


void ObjectContainer::pushBack(Object *item){
    if(iUsed == iSize)
        resize(int(iSize+5));
    objects[iUsed] = item;
    iUsed++;
}


void ObjectContainer::remove(int index){
    if(index < 0 || unsigned(index) >= iUsed)
        throw std::range_error("Nonexistent item");

    if(iUsed == 1)
    {
        erase();
        return;
    }

    for(int i = index; i < int(iUsed)-1; i++)
    {
        objects[i] = objects[i+1];
    }
    iUsed--;

    if(iUsed+5 <= iSize){
        resize(int(iUsed));
    }
}


void ObjectContainer::remove(Object* toRemove){
    int index;
    bool found = 0;
    for(index = 0; index < iUsed; index++){
        if(objects[index] == toRemove){
            found = 1;
            break;
        }
    }

    if(!found) return;

    remove(index);
}








