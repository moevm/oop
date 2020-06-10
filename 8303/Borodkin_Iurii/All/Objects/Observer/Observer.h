#ifndef OBSERVER_H
#define OBSERVER_H
#include "../Base.h"
#include <QDebug>
#include <list>
#include <QTextBrowser>

class MonitorBase;

class IObserver
{
public:
    virtual void event(const MonitorBase&, QString* = nullptr) = 0;
    virtual ~IObserver() = default;
};

class MonitorBase
{
public:
    void addObserver(IObserver&);
    void removeObserver(IObserver&);
    const Base* get() const;
    void resetBase(Base&, QString* = nullptr);
private:
    Base* base;
    std::list <IObserver*> observers;
    void notify(QString* = nullptr);
};

class Reflector : public IObserver
{
public:
    void event(const MonitorBase &, QString* = nullptr) final;
};


#endif // OBSERVER_H
