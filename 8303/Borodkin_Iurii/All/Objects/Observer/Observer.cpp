#include "Observer.h"

void MonitorBase::notify(QString* stream)
{
    for (auto &observer : observers)
        observer->event(*this, stream);
}

void MonitorBase::addObserver(IObserver &ref)
{
    observers.push_back(&ref);
}

void MonitorBase::removeObserver(IObserver &ref)
{
    observers.remove(&ref);
}

const Base* MonitorBase::get() const
{
    return base;
}

void MonitorBase::resetBase(Base &newBase, QString* stream)
{
    base = &newBase;
    notify(stream);
}

void Reflector::event(const MonitorBase &ref, QString* stream)
{
    auto units = ref.get()->getHeap().getUnits();
    for (auto unit : units)
    {
        if (stream)
        {
            stream->append(QString(unit->type().c_str()) + '\n');
        }
        else
            qDebug() << unit->type().c_str();
    }
}
