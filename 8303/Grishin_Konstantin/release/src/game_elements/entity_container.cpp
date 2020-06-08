#include "entity_container.h"

#include "entity.h"

EntityContainer::EntityContainer():
    iSize(0), iUsed(0), p_array(nullptr)
{}


EntityContainer::~EntityContainer(){
    delete [] p_array;
}


EntityContainer::EntityContainer(EntityContainer&& other){
    std::swap(iSize, other.iSize);
    std::swap(iUsed, other.iUsed);
    std::swap(p_array, other.p_array);
}


EntityContainer& EntityContainer::operator=(EntityContainer &&other){
    std::swap(iSize, other.iSize);
    std::swap(iUsed, other.iUsed);
    std::swap(p_array, other.p_array);
    return *this;
}


void EntityContainer::resize(unsigned int iNewSize){
    if(iSize == unsigned(iNewSize))
        return;

    if(iNewSize <= 0){
        clear();
        return;
    }

    auto new_array = new Entity*[unsigned(iNewSize)];
    if(iSize > 0)
    {
        size_t uToCopySize = (iSize > size_t(iNewSize)) ? iNewSize : iSize;

        for(size_t i = 0; i < uToCopySize; i++)
        {
            new_array[i] = p_array[i];
        }
    }

    delete [] p_array;
    p_array = new_array;
    iSize = size_t(iNewSize);
}


Entity*
EntityContainer::checkIndexAndGet(size_t pos) const
{
    if(pos >= iUsed)
    {
        throw std::out_of_range("out if range");
    }
    return (p_array[pos]);
}


Entity*
EntityContainer::at(size_t pos){
    return checkIndexAndGet(pos);
}


const Entity*
EntityContainer::at(size_t pos) const{
    return checkIndexAndGet(pos);
}


Entity*
EntityContainer::operator[](size_t pos){
    return (p_array[pos]);
}


const Entity*
EntityContainer::operator[](size_t pos) const{
    return (p_array[pos]);
}


void EntityContainer::push_back(Entity* item){
    if(iUsed == iSize){
        resize(iUsed+5);
    }
    p_array[iUsed] = item;
    iUsed++;
}


void EntityContainer::clear(){
    delete [] p_array;
    iSize = 0;
    iUsed = 0;
    p_array = nullptr;
}


void EntityContainer::remove(size_t index){
    if(index >= iUsed)
    {
        throw std::range_error("out of range");
    }

    if(iUsed == 1){
        clear();
        return;
    }

    for(size_t i = index; i < iSize-1; i++)
    {
        p_array[i] = p_array[i+1];
    }
    iUsed--;

    if(iUsed+5 <= iSize)
        resize(iUsed);
}


void EntityContainer::remove(const Entity* to_remove){
    size_t index;
    bool found = 0;
    for(index = 0; index < iUsed; index++){
        if(p_array[index] ==  to_remove){
            found = 1;
            break;
        }
    }

    if(!found) return;

    remove(index);
}


size_t EntityContainer::size() const{
    return iUsed;
}


bool EntityContainer::empty() const{
    return iUsed == 0;
}




















