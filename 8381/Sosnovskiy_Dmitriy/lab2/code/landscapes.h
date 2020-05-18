#ifndef LANDSCAPES_H
#define LANDSCAPES_H
#include "iprintable.h"

class ILandscape : public IPrintable
{
public:
    virtual ~ILandscape() = default;
    virtual bool canHoldCreature() const = 0;

    virtual ILandscape* copy() = 0;
};

class LandscapeProxy : public ILandscape
{
private:
    ILandscape* landscape;
public:
    LandscapeProxy(ILandscape* landscape)
    {
        this->landscape = landscape;
    }

    bool canHoldCreature() const override
    {
        return landscape->canHoldCreature();
    }

    QString getClass() override { return landscape->getClass(); }

    ILandscape* copy() override { return new LandscapeProxy(landscape); }
};

class Mountains : public ILandscape
{
public:
    bool canHoldCreature() const override { return true; }
    QString getClass() override { return "Mountains"; }
    ILandscape* copy() override {
        return new Mountains();
    }
};


class Ground : public ILandscape
{
public:
    bool canHoldCreature() const override { return true; }
    QString getClass() override { return "Ground"; }
    ILandscape* copy() override{
        return new Ground();
    }
};


class Water : public ILandscape
{
public:
    bool canHoldCreature() const override { return false; }
    QString getClass() override { return "Water"; }
    ILandscape* copy() override{
        return new Water();
    }
};


#endif // LANDSCAPES_H
