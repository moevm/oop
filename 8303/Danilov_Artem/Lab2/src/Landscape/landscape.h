#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <iostream>
class Landscape
{
public:
    virtual std::string getType() const = 0;
//    virtual bool canMove() = 0;
//    virtual bool canAttack() = 0;
    virtual ~Landscape() = default;
};

class River : public Landscape
{
protected:
    std::string type = "River";
public:
    std::string getType() const {return  type;};
};

class Forest : public Landscape
{
protected:
    std::string type = "Forest";
public:
    std::string getType() const {return  type;};
};


class Desert : public Landscape
{
protected:
    std::string type = "Desert";
public:
    std::string getType() const {return  type;};
};

#endif // LANDSCAPE_H
