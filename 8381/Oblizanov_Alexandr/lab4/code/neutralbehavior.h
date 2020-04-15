#ifndef NEUTRALBEHAVIOR_H
#define NEUTRALBEHAVIOR_H

#include "logadapter.h"

class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual void unitInfluence(IUnit *unit) = 0;
};

//CHEST BEHAVIOR

class AttackChestStrategy : public Strategy
{
public:
    AttackChestStrategy(int secret)
        :secret(secret) {}
    void unitInfluence(IUnit *unit) {
        unit->setAttackBonus(secret);
    }
private:
    int secret;
};

class SupportChestStrategy : public Strategy
{
public:
    SupportChestStrategy(int secret)
        :secret(secret) {}
    void unitInfluence(IUnit *unit) {
        unit->setSecurityBonus(secret);
    }
private:
    int secret;
};

class SimpleChestStrategy : public Strategy
{
public:
    SimpleChestStrategy(int secret)
        :secret(secret) {}
    void unitInfluence(IUnit *unit) {
        unit->setCharacteristicsBonus(secret);
    }
private:
    int secret;
};

class ChestStrategySelector : public Strategy
{
public:
    ChestStrategySelector(int secret)
        :secret(secret) {}
    void unitInfluence(IUnit *unit) {
        switch (unit->getType()) {
        case SIM_BS:
        case SIM_SC:
            strategy = new SimpleChestStrategy(secret);
            strategy->unitInfluence(unit);
            break;
        case SUP_BS:
        case SUP_SC:
            strategy = new SupportChestStrategy(secret);
            strategy->unitInfluence(unit);
            break;
        case ATT_BS:
        case ATT_SC:
            strategy = new AttackChestStrategy(secret);
            strategy->unitInfluence(unit);
            break;
        default:
            break;
        }
        delete strategy;
    }
private:
    Strategy *strategy = nullptr;
    int secret;
};

//KEYGEN BEHAVIOR

class AttackKeygenStrategy : public Strategy
{
public:
    AttackKeygenStrategy(int danger, int threat)
        :danger(danger), threat(threat) {}
    void unitInfluence(IUnit *unit) {
        unit->setAttackBonus(threat);
        unit->setSecurityBonus(-danger/5);
    }
private:
    int danger;
    int threat;
};

class BasicKeygenStrategy : public Strategy
{
public:
    BasicKeygenStrategy(int danger, int threat)
        :danger(danger), threat(threat) {}
    void unitInfluence(IUnit *unit) {
        unit->setAttackBonus(threat);
        unit->setSecurityBonus(-danger);
    }
private:
    int danger;
    int threat;
};

class KeygenStrategySelector : public Strategy
{
public:
    KeygenStrategySelector(int danger, int threat)
        :danger(danger), threat(threat) {}
    void unitInfluence(IUnit *unit) {
        switch (unit->getType()) {
        case ATT_BS:
        case ATT_SC:
            strategy = new AttackKeygenStrategy(danger, threat);
            break;
        default:
            strategy = new BasicKeygenStrategy(danger, threat);
        }
        strategy->unitInfluence(unit);
        delete strategy;
    }
private:
    Strategy *strategy = nullptr;
    int danger;
    int threat;
};

//ANTIVIRUS BEHAVIOR

class SupportAntivirusStrategy : public Strategy
{
public:
    SupportAntivirusStrategy (int efficiency, int slowdown)
        : efficiency(efficiency), slowdown(slowdown) {}
    void unitInfluence(IUnit *unit) {
        unit->setSecurityBonus(efficiency);
        unit->setAttackBonus(-slowdown/2);
    }
private:
    int efficiency;
    int slowdown;
};

class BasicAntivirusStrategy : public Strategy
{
public:
    BasicAntivirusStrategy (int efficiency, int slowdown)
        : efficiency(efficiency), slowdown(slowdown) {}
    void unitInfluence(IUnit *unit) {
        unit->setSecurityBonus(efficiency/3);
        unit->setAttackBonus(-slowdown);
    }
private:
    int efficiency;
    int slowdown;
};

class AntivirusStrategySelector : public Strategy
{
public:
    AntivirusStrategySelector (int efficiency, int slowdown)
        : efficiency(efficiency), slowdown(slowdown) {}
    void unitInfluence(IUnit *unit) {
        switch (unit->getType()) {
        case SUP_BS:
        case SUP_SC:
            strategy = new SupportAntivirusStrategy(efficiency, slowdown);
            break;
        default:
            strategy = new BasicAntivirusStrategy(efficiency, slowdown);
        }
        strategy->unitInfluence(unit);
        delete strategy;
    }
private:
    Strategy *strategy = nullptr;
    int efficiency;
    int slowdown;
};

//DATA BEHAVIOR

class SCDataStrategy : public Strategy
{
public:
    SCDataStrategy(int knowledge)
        :knowledge(knowledge) {}
    void unitInfluence(IUnit *unit) {
        unit->setSecurityBonus(knowledge);
        unit->setAttackBonus(knowledge);
    }
private:
    int knowledge;
};

class BSDataStrategy : public Strategy
{
public:
    BSDataStrategy(int knowledge)
        :knowledge(knowledge) {}
    void unitInfluence(IUnit *unit) {
        unit->setSecurityBonus(knowledge/5);
        unit->setAttackBonus(knowledge/5);
    }
private:
    int knowledge;
};

class DataStrategySelector : public Strategy
{
public:
    DataStrategySelector(int knowledge)
        :knowledge(knowledge) {}
    void unitInfluence(IUnit *unit) {
       if (unit->getType()%2 == 0)
           strategy = new SCDataStrategy(knowledge);
       else
           strategy = new BSDataStrategy(knowledge);
       strategy->unitInfluence(unit);
       delete strategy;
    }
private:
    Strategy *strategy = nullptr;
    int knowledge;
};

#endif // NEUTRALBEHAVIOR_H
