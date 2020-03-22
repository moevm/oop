#ifndef OOP_IWIZARD_H
#define OOP_IWIZARD_H

class IWizard
{
protected:
    virtual void magicFist() = 0;
    virtual void healing() = 0;

    virtual ~IWizard() = default;
};

#endif //OOP_IWIZARD_H
