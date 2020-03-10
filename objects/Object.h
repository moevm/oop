#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <utility>
#include <objects/Attributes.h>

enum class Moves : int
{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

class Object
{
protected:
    Attributes* attr;
    std::string _name;
    explicit Object(std::string = "");
public:
    unsigned health() const;
    unsigned range() const;
    unsigned damage() const;
    unsigned armor() const;
    unsigned mana() const;
    std::string &name();
    virtual std::string type() const = 0;
    virtual ~Object();
};

#endif // OBJECT_H
