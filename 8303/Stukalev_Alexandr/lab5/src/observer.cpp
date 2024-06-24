#include "observer.h"

void Subject::addObserver(Observer* observer)
{
    views.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
    std::vector<Observer*>::iterator i = views.begin();
    while( i != views.end())
    {
        if (*i = observer)
        {
            views.erase(i);
            return;
        }
    }
}

void  Subject::notify()
{
    for (Observer* observer: views)
    {
        observer->update(this);
    }
}
