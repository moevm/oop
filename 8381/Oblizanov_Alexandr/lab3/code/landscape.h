#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "objects.h"

class Landscape : public FieldLandscape
{
public:
    virtual LandType getType() {
        return type;
    }
    virtual std::string shortName() = 0;
    virtual void setBadLand() = 0;
    virtual void unitInfluence(IUnit *unit) = 0;
    virtual FieldLandscape *landCopy() = 0;
protected:
    LandType type;
};

class OpenLandscape : public Landscape
{
public:
    OpenLandscape() {type = OPEN;}
    void setBadLand() {type = OPEN_B;}
    std::string shortName() {
        if (type == OPEN)
            return "OPEN";
        return "OPENB";
    }
    void unitInfluence(IUnit *unit) {
        switch (unit->getType()) {
        case SIM_BS:
        case SIM_SC:
            unit->setCharacteristicsBonus(20);
            break;
        }
        if (type == OPEN_B)
            unit->setSecurityBonus(-10);
    }
    FieldLandscape *landCopy() {
        return new OpenLandscape(*this);
    }
};

class VPNLandscape : public Landscape
{
public:
    VPNLandscape() {type = VPN;}
    void setBadLand() {type = VPN_B;}
    std::string shortName() {
        if (type == VPN)
            return "VPN";
        return "VPNB";
    }
    void unitInfluence(IUnit *unit) {
        switch (unit->getType()) {
        case SUP_BS:
        case SUP_SC:
            unit->setSecurityBonus(20);
            break;
        }
        if (type == VPN_B)
            unit->setAttackBonus(-10);
    }
    FieldLandscape *landCopy() {
        return new VPNLandscape(*this);
    }
};

class FastLandscape : public Landscape
{
public:
    FastLandscape() {type = FAST;}
    void setBadLand() {type = FAST_B;}
    std::string shortName() {
        if (type == FAST)
            return "FAST";
        return "FASTB";
    }
    void unitInfluence(IUnit *unit) {
        switch (unit->getType()) {
        case ATT_BS:
        case ATT_SC:
            unit->setAttackBonus(20);
            break;
        }
        if (type == FAST_B)
            unit->setSecurityBonus(-10);
    }
    FieldLandscape *landCopy() {
        return new FastLandscape(*this);
    }
};

class ProxyLandscape : public FieldLandscape
{
public:
    ~ProxyLandscape() {
        delete land;
    }
    ProxyLandscape(LandType type) {
        switch (type) {
        case OPEN:
        case OPEN_B:
            land = new OpenLandscape();
            break;
        case VPN:
        case VPN_B:
            land = new VPNLandscape();
            break;
        case FAST:
        case FAST_B:
            land = new FastLandscape();
            break;
        }
        if (type == FAST_B || type == OPEN_B || type == VPN_B)
            land->setBadLand();
    }

    std::string shortName() {
        return land->shortName();
    }

    LandType getType() {
        return land->getType();
    }
    void setBadLand() {
        land->setBadLand();
    }
    void unitInfluence(IUnit *unit) {
        switch (land->getType()) {
        case VPN:
        case VPN_B:
        case FAST:
        case FAST_B:
            if (unit->getType() == SIM_BS || unit->getType() == SIM_SC)
                throw std::invalid_argument("unit " + unit->shortName() + " cannon be placed on VPN/FAST landscape");
            break;
        default:
            break;
        }
        land->unitInfluence(unit);
    }
    FieldLandscape *landCopy() {
        return new ProxyLandscape(land->getType());
    }
private:
    Landscape *land;
};

#endif // LANDSCAPE_H
