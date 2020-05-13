//
// Created by kot on 08.05.2020.
//

#include "subject.h"

void Subject::attach(Observer * observer)
{
    listObserver.push_back(observer);
}

void Subject::detach(Observer * observer)
{
    for (auto iter = listObserver.begin(); iter != listObserver.end(); iter++)
        if (*iter == observer)
        {
            listObserver.erase(iter);
            return;
        }
}

void Subject::notify()
{
    for (auto* observer : listObserver) {
        observer->update(this);
    }
}

