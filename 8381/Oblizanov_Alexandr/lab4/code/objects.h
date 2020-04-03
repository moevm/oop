#ifndef UNIT_H
#define UNIT_H

#include "neutralbehavior.h"


//ITEM OBJECTS
class Unit;

class Unit : public IUnit
{
public:
    Unit(){}
    Unit(Unit &unit);

    virtual bool isMovable() {
       return movable;
    }


    virtual int getType() = 0;

    virtual std::string shortName() = 0;
    virtual std::string about();
    virtual FieldItem *itemCopy() = 0;

    virtual Skills getAttackSkills() const;
    virtual Skills getSecuritySkills() const;
    virtual Skills getCharacteristics() const;

    virtual void setAttackBonus(int bonus);
    virtual void setSecurityBonus(int bonus);
    virtual void setCharacteristicsBonus(int bonus);

    virtual void setMoveMediator(MoveMediator *value);
    virtual void setAttackMediator(IAttackMediator *value);

    virtual bool receiveAttack(IUnit *unit);

    virtual bool attack(int x, int y);
    virtual void move(int x, int y);

    virtual void unitInfluence(IUnit *unit) {}

    virtual IUnit& operator+=(FieldItem *item);

    unsigned getBaseNumber() const;

protected:
    std::string name;
    bool movable = true;
    Skills attackSkills;
    Skills securitySkills;
    Skills characteristics;
    unsigned baseNumber;
    MoveMediator *moveMediator = nullptr;
    IBaseObserver *baseObserver;
    IAttackMediator *attackMediator;
};

class CyberScientist : public Unit
{
public:
    virtual FieldItem *itemCopy() = 0;
};

class SimpleCyberScientist : public CyberScientist
{
public:
    SimpleCyberScientist(IBaseObserver *base);
    virtual ~SimpleCyberScientist()
    {
        delete moveMediator;
        baseObserver->deleteUpdate(this);
    }
    int getType() {
        return SIM_SC;
    }
    std::string shortName() {return "SmpCS";}
    FieldItem *itemCopy() {
        return new SimpleCyberScientist(*this);
    }
};

class AttackCyberScientist : public CyberScientist
{
public:
    AttackCyberScientist(IBaseObserver *base);
    virtual ~AttackCyberScientist()
    {
        delete moveMediator;
        baseObserver->deleteUpdate(this);
    }
    int getType() {
        return ATT_SC;
    }
    std::string shortName() {return "AttCS";}
    FieldItem *itemCopy() {
        return new AttackCyberScientist(*this);
    }
};

class SupportCyberScientist : public CyberScientist
{
public:
    SupportCyberScientist(IBaseObserver *base);
    virtual ~SupportCyberScientist()
    {
        delete moveMediator;
        baseObserver->deleteUpdate(this);
    }
    int getType() {
        return SUP_SC;
    }
    std::string shortName() {return "SupCS";}
    FieldItem *itemCopy() {
        return new SupportCyberScientist(*this);
    }
};

class CyberBerserk : public Unit
{
public:
    virtual FieldItem *itemCopy() = 0;
    virtual std::string learnFrom(CyberScientist &teacher) = 0;
};

class SimpleCyberBerserk : public CyberBerserk
{
public:
    SimpleCyberBerserk (IBaseObserver *base);
    virtual ~SimpleCyberBerserk()
    {
        delete moveMediator;
        baseObserver->deleteUpdate(this);
    }
    int getType() {
        return SIM_BS;
    }
    std::string learnFrom(CyberScientist &teacher) {
        return name + " trying to learn simple from " + teacher.about();
    }
    std::string shortName() {return "SmpCB";}
    FieldItem *itemCopy() {
        return new SimpleCyberBerserk(*this);
    }
};

class AttackCyberBerserk : public CyberBerserk
{
public:
    AttackCyberBerserk (IBaseObserver *base);
    virtual ~AttackCyberBerserk()
    {
        delete moveMediator;
        baseObserver->deleteUpdate(this);
    }
    int getType() {
        return ATT_BS;
    }
    std::string learnFrom(CyberScientist &teacher) {
        if (teacher.getAttackSkills().getBonus() > this->attackSkills.getBonus())
            this->attackSkills.setBonus(teacher.getAttackSkills().getBonus());
        return name + " trying to learn attack from " + teacher.about();
    }
    std::string shortName() {return "AttCB";}
    FieldItem *itemCopy() {
        return new AttackCyberBerserk(*this);
    }
};

class SupportCyberBerserk : public CyberBerserk
{
public:
    SupportCyberBerserk (IBaseObserver *base);
    virtual ~SupportCyberBerserk()
    {
        delete moveMediator;
        baseObserver->deleteUpdate(this);
    }
    int getType() {
        return SUP_BS;
    }
    std::string learnFrom(CyberScientist &teacher) {
        if (teacher.getSecuritySkills().getBonus() > this->securitySkills.getBonus())
            this->securitySkills.setBonus(teacher.getSecuritySkills().getBonus());
        return name + " trying to learn support from " + teacher.about();
    }
    std::string shortName() {return "SupCB";}
    FieldItem *itemCopy() {
        return new SupportCyberBerserk(*this);
    }
};

//NEUTRAL OBJECTS


class Chest : public INeutral
{
public:
    void setMoveMediator(MoveMediator *value) {delete value;}
    bool isMovable() {
        return false;
    }
    std::string about() {
        return "Chest neutral object. OPEN ME!";
    }
    std::string shortName() {
        return "CHEST";
    }
    FieldItem * itemCopy() {
        return new Chest(*this);
    }

    Chest(int secret)
        :secret(secret) {}
    int getType() {
        return CHEST;
    }
    void unitInfluence(IUnit *unit) {
        ChestStrategySelector strategy(secret);
        strategy.unitInfluence(unit);
    }
private:
    int secret;
};

class Keygen : public INeutral
{
public:
    void setMoveMediator(MoveMediator *value) {delete value;}
    bool isMovable() {
        return false;
    }
    std::string about() {
        return "Keygen neutral object. HACK SMB!";
    }
    std::string shortName() {
        return "KEYGEN";
    }
    FieldItem * itemCopy() {
        return new Keygen(*this);
    }

    Keygen(int danger, int threat)
        :danger(danger), threat(threat) {}
    int getType() {
        return KEYGEN;
    }
    void unitInfluence(IUnit *unit) {
        KeygenStrategySelector strategy(danger, threat);
        strategy.unitInfluence(unit);
    }
private:
    int danger;
    int threat;
};

class Antivirus : public INeutral
{
public:
    void setMoveMediator(MoveMediator *value) {delete value;}
    bool isMovable() {
        return false;
    }
    std::string about() {
        return "Antivirus neutral object. PROTECT YOURSELF!";
    }
    std::string shortName() {
        return "AVRS";
    }
    FieldItem * itemCopy() {
        return new Antivirus(*this);
    }

    Antivirus(int efficiency, int slowdown)
        :efficiency(efficiency), slowdown(slowdown) {}
    int getType() {
        return ANTIVIRUS;
    }
    void unitInfluence(IUnit *unit) {
        AntivirusStrategySelector strategy(efficiency, slowdown);
        strategy.unitInfluence(unit);
    }
private:
    int efficiency;
    int slowdown;
};

class Data : public INeutral
{
public:
    void setMoveMediator(MoveMediator *value) {delete value;}
    bool isMovable() {
        return false;
    }
    std::string about() {
        return "Data neutral object. READ ME!";
    }
    std::string shortName() {
        return "DATA";
    }
    FieldItem * itemCopy() {
        return new Data(*this);
    }

    Data(int knowledge)
        :knowledge(knowledge) {}
    int getType() {
        return DATA;
    }
    void unitInfluence(IUnit *unit) {
        DataStrategySelector strategy(knowledge);
        strategy.unitInfluence(unit);
    }
private:
    int knowledge;
};

#endif // UNIT_H
