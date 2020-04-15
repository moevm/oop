#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include "landscape.h"

class DeviceFactory {
public:
    virtual ~DeviceFactory() = default;
    virtual CyberScientist *createCyberScientist(IBaseObserver *base) = 0;
    virtual CyberBerserk *createCyberBerserk(IBaseObserver *base) = 0;
};

class SimpleDevice : public DeviceFactory {
public:
    CyberBerserk * createCyberBerserk(IBaseObserver *base) {
        return new SimpleCyberBerserk(base);
    }
    CyberScientist * createCyberScientist(IBaseObserver *base) {
        return new SimpleCyberScientist(base);
    }
};

class AttackDevice : public DeviceFactory {
public:
    CyberBerserk * createCyberBerserk(IBaseObserver *base) {
        return new AttackCyberBerserk(base);
    }
    CyberScientist * createCyberScientist(IBaseObserver *base) {
        return new AttackCyberScientist(base);
    }
};

class SupportDevice : public DeviceFactory {
public:
    CyberBerserk * createCyberBerserk(IBaseObserver *base) {
        return new SupportCyberBerserk(base);
    }
    CyberScientist * createCyberScientist(IBaseObserver *base) {
        return new SupportCyberScientist(base);
    }
};


#endif // UNITFACTORY_H
