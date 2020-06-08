//
// Created by therealyou on 01.06.2020.
//

#ifndef LAB1_STATE_H
#define LAB1_STATE_H

#include "BaseHandler.h"

class State
{
public:
    virtual void handle(std::string command, BaseHandler* handler, std::string mode) = 0;
};

class State1 : public State
{
    void handle(std::string command, BaseHandler* handler, std::string mode) override
    {
        handler->handle(command, 1, mode);
    }
};

class State2 : public State
{
    void handle(std::string command, BaseHandler* handler, std::string mode) override
    {
        handler->handle(command, 2, mode);
    }
};

class State3 :  public State
{
    void handle(std::string command, BaseHandler* handler, std::string mode) override
    {
        handler->handle(command, 3, mode);
    }
};

#endif //LAB1_STATE_H
