#ifndef ENTITYCONTAINER_H
#define ENTITYCONTAINER_H

#include <cstddef>
#include <iterator>

class Entity;


class EntityContainer
{


private:
    unsigned int iSize;
    unsigned int iUsed;
    Entity **p_array;

    void resize(unsigned int iNewSize);
    Entity* checkIndexAndGet(size_t pos) const;

public:
    EntityContainer();
    ~EntityContainer();

    EntityContainer(const EntityContainer& other) = delete;
    EntityContainer(EntityContainer&& other);

    EntityContainer& operator=(EntityContainer&& other);

    Entity* at(size_t pos);
    const Entity* at(size_t pos) const;

    Entity* operator[](size_t pos);
    const Entity* operator[](size_t pos) const;

    void push_back(Entity* item);
    void clear();

    void remove(size_t index);
    void remove(const Entity* to_remove);

    size_t size() const;
    bool empty() const;
};

#endif // ENTITYCONTAINER_H
