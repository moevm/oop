//
// Created by anton on 15.03.2020.
//

#include "Subject.h"
void Subject::deleteObserver(Observer *observer)
{
    for(auto iter = observers.begin(); iter != observers.end(); iter++){
        if (*iter == observer){
            observers.erase(iter);
            return;
        }
    }
}

void Subject::addObserver(Observer *observer)
{
    observers.push_back(observer);
}

void Subject::notify()
{
    for (auto obs : observers)
        obs->update(this);
}