#ifndef OOP_ICAVALRY_H
#define OOP_ICAVALRY_H

class ICavalry
{
protected:
    virtual void postMortem() = 0;
    virtual void armament() = 0;

    virtual ~ICavalry() = default;
};

#endif //OOP_ICAVALRY_H
