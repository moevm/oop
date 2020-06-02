#ifndef ARMOR_H
#define ARMOR_H

#include "neutralObj.h"
class Armor{
public:
    virtual ~Armor()=default;
    virtual void use(Unit& unit)=0;
    virtual NeutralType type()=0;
};

class Visor : public Armor{

public:
    void use(Unit &unit);
    NeutralType type();
};

class Lat : public Armor{

public:
    void use(Unit &unit);
    NeutralType type();
};

class Boots : public Armor{

public:
    void use(Unit &unit);
    NeutralType type();
};

class GetArmor : public NeutralObj
{

private:
    Armor* armor;

public:
    GetArmor(Armor*);
    void operator +=(Unit &unit);
    ~GetArmor();
    string characteristic();
    string getType() const;
    NeutralType getTypeEnum();
};

#endif // ARMOR_H
