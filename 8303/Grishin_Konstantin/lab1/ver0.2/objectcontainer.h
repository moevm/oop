#ifndef OBJECTCONTAINER_H
#define OBJECTCONTAINER_H

class Object;

class ObjectContainer
{
private:
    unsigned int iSize;
    unsigned int iUsed;
    Object **objects;

    void resize(int iNewSize);

public:
    ObjectContainer();
    ~ObjectContainer();

    void erase();
    Object* operator[](int index) const;
    unsigned int length() const;

    void pushBack(Object* item);
    void remove(int index); // delete item with index
    void remove(Object*);
};

#endif // OBJECTCONTAINER_H
