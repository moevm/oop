//
// Created by anton on 05.05.2020.
//

#ifndef OOP_1_RULES_H
#define OOP_1_RULES_H

#include "State.h"

class Rule
{
protected:
    State* state1;
    State* state2;
    State* state3;
    State* current;

public:
    Rule();

    virtual Field* createField(Adapter* adapter) = 0;

    virtual void handle(std::string command, BaseHandler* handler, int playersNumber, std::string mode) = 0;

    void nextPlayer(int playersNumber);
};

class Rule1 : public Rule
{
public:
    Field* createField(Adapter* adapter) override;

    void handle(std::string command, BaseHandler* handler, int playersNumber, std::string mode) override;

    int loser(Field* field, int playersNumber);
};

class Rule2 : public Rule
{
public:
    Field* createField(Adapter* adapter) override;

    void handle(std::string command, BaseHandler* handler, int playersNumber, std::string mode) override;

    int loser(Field* field, int playersNumber);
};
#endif //OOP_1_RULES_H
