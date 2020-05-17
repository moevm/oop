#ifndef OOP_1_STATE_H
#include <string>
#include "Handler.h"
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

#define OOP_1_STATE_H

#endif //OOP_1_STATE_H
