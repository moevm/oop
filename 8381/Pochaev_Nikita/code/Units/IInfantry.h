#ifndef OOP_IINFANTRY_H
#define OOP_IINFANTRY_H

class IInfantry
{
protected:
    virtual void closeTheRanks() = 0;
    virtual void fury() = 0;

    virtual ~IInfantry() = default;
};

#endif //OOP_IINFANTRY_H
