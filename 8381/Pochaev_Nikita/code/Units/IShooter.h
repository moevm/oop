#ifndef OOP_ISHOOTER_H
#define OOP_ISHOOTER_H

class IShooter
{
protected:
    virtual void shot() = 0;
    virtual void canopyShooting() = 0;

    virtual ~IShooter() = default;
};

#endif //OOP_ISHOOTER_H
