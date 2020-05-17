#ifndef STATE_H
#define STATE_H

#include <string>

#include "ChainOfCommand.h"

class State{
public:
    virtual void handle(std::string command, chainOfResponsibility *basecomm) = 0;
};

class State1: public State{
public:
    void handle(std::string command, chainOfResponsibility *basecomm) override {
        basecomm->chainOR(command, "0");
    }
};

class State2: public State{
public:
    void handle(std::string command, chainOfResponsibility *basecomm) override {
        basecomm->chainOR(command, "1");
    }
};

#endif //STATE_H
