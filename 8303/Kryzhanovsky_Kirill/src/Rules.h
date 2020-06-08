//
// Created by therealyou on 01.06.2020.
//

#ifndef LAB1_RULES_H
#define LAB1_RULES_H

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

    virtual GameField* createField(Adapter* adapter) = 0;

    virtual void handle(std::string command, BaseHandler* handler, int playersNumber, std::string mode) = 0;

    void nextPlayer(int playersNumber);
};

class Rule1 : public Rule
{
public:
    GameField* createField(Adapter* adapter) override;

    void handle(std::string command, BaseHandler* handler, int playersNumber, std::string mode) override;

    int loser(GameField* field, int playersNumber);
};

class Rule2 : public Rule
{
public:
    GameField* createField(Adapter* adapter) override;

    void handle(std::string command, BaseHandler* handler, int playersNumber, std::string mode) override;

    int loser(GameField* gameField, int playersNumber);
};


#endif //LAB1_RULES_H
