#ifndef LAND_H
#define LAND_H

#include "libraries.h"

class Land
{
public:
    virtual std::string getType() const = 0;
//    virtual Land *itemCopy() = 0;
};

class River : public Land
{
protected:
    std::string type = "R";
public:
    std::string getType() const;
//    Land * itemCopy(){
//        return new River(*this);
//    }
};

class Forest : public Land
{
protected:
    std::string type = "F";
public:
    std::string getType() const;
//    Land * itemCopy(){
//        return new Forest(*this);
//    }
};


class Desert : public Land
{
protected:
    std::string type = "D";
public:
    std::string getType() const;
//    Land * itemCopy(){
//        return new Desert(*this);
//    }
};


class Proxy : public Land
{
private:
    Land* landscape;

public:
    Proxy(std::string type);
    bool checkMoveAccess(std::string unitType) const;
    bool checkAttackAccess(std::string unitType) const;
    std::string getType() const;
};



#endif // LAND_H
