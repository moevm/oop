#ifndef CHAINOFRESONSIBILITY_H
#define CHAINOFRESONSIBILITY_H


class ChainOfResonsibility
{
    friend class Command;

    int priority;

public:
    ChainOfResonsibility(int);
};

#endif // CHAINOFRESONSIBILITY_H
