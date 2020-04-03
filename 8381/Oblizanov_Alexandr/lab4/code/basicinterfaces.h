#ifndef BASICINTERFACES_H
#define BASICINTERFACES_H

#include "libraries.h"
#include "skills.h"

class Field;
class MoveMediator;
class IUnit;
class Unit;
class UIFacade;
class IAttackMediator;

class Time;

class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual bool isActive() = 0;
    virtual void print() = 0;
    virtual void printLog(std::string output) = 0;
    virtual void printTime() = 0;
    virtual Time *getLocalTime() const = 0;
    virtual std::string getInfo() const = 0;
    virtual void setInfo(const std::string &value) = 0;
};

class ILogAdapter
{
public:
    virtual ~ILogAdapter() = default;
    virtual void setLogger(ILogger *logger) = 0;
    virtual void setType(const LogType &value) = 0;
    virtual void pushLog(LogEvent event, std::vector<int> param = {}) = 0;
};

class FieldItem
{
public:
    virtual ~FieldItem() = default;
    virtual bool isMovable() = 0;
    virtual std::string about() = 0;
    virtual std::string shortName() = 0;
    virtual FieldItem *itemCopy() = 0;
    virtual void unitInfluence(IUnit *unit) = 0;
    virtual int getType() = 0;
    virtual void setMoveMediator(MoveMediator *value) = 0;
};

class INeutral : public FieldItem
{
public:
    virtual ~INeutral() = default;
    virtual bool isMovable() = 0;
    virtual std::string about() = 0;
    virtual std::string shortName() = 0;
    virtual FieldItem *itemCopy() = 0;
    virtual int getType() = 0;
    virtual void setMoveMediator(MoveMediator *value) = 0;
};

class IUnit : public FieldItem
{
public:
    virtual ~IUnit() = default;
    virtual void move(int x, int y) = 0;
    virtual bool attack(int x, int y) = 0;
    virtual int getType() = 0;
    virtual void setAttackBonus(int bonus) = 0;
    virtual void setSecurityBonus(int bonus) = 0;
    virtual void setCharacteristicsBonus(int bonus) = 0;

    virtual Skills getAttackSkills() const = 0;
    virtual Skills getSecuritySkills() const = 0;
    virtual Skills getCharacteristics() const = 0;
    virtual unsigned getBaseNumber() const = 0;
    virtual void setAttackMediator(IAttackMediator *value) = 0;

    virtual bool receiveAttack(IUnit *unit) = 0;

    virtual IUnit& operator+=(FieldItem *item) = 0;
};

class FieldLandscape
{
public:
    virtual ~FieldLandscape() = default;
    virtual LandType getType() = 0;
    virtual std::string shortName() = 0;
    virtual void unitInfluence(IUnit *unit) = 0;
    virtual void setBadLand() = 0;
    virtual FieldLandscape *landCopy() = 0;
};

class ICreateMediator {
public:
    virtual ~ICreateMediator() = default;
    virtual void Notify(FieldItem *sender, FieldItem *unit, unsigned x, unsigned y) = 0;
};

class MoveMediator {
public:
    MoveMediator(Field *field, FieldItem *item);
    void Notify(IUnit *sender, int x, int y);
private:
    Field *field;
    FieldItem *item;
};

class IAttackMediator
{
public:
    virtual ~IAttackMediator() = default;
    virtual bool attack(IUnit *attacker, int deltaX, int deltaY) = 0;
};


class IGameMediator {
public:
    virtual ~IGameMediator() = default;
    virtual void Notify(IUnit *unit, bool add) = 0;
};

class IBase : public FieldItem
{
    virtual void reduceStability(unsigned value) = 0;
    virtual void setCreateMediator(ICreateMediator *value) = 0;
    virtual void setGameMediator(IGameMediator *value) = 0;
};

class IBaseObserver
{
public:
    virtual ~IBaseObserver() = default;
    virtual void deleteUpdate(Unit *unit) = 0;
    virtual unsigned getNumber() = 0;
};

class IGame {
public:
    virtual ~IGame() = default;
    virtual void createBase(std::string name, unsigned limit, unsigned x, unsigned y) = 0;
    virtual Field *getField() const = 0;
};

class IFacadeMediator {
public:
    virtual ~IFacadeMediator() = default;
    virtual UIFacade *getFacade() const = 0;
    virtual void sendString(RequestType type, std::string answer) = 0;
};

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual std::vector<int> exec() = 0;
};





#endif // BASICINTERFACES_H
