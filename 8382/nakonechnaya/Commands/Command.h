#ifndef OOP_COMMAND_H
#define OOP_COMMAND_H
#include "../Loggers/LogProxy.h"
#include "../Loggers/Adapter.h"
#include "Rules.h"
#include <cmath>

class Command{
public:
    virtual ~Command(){};
    virtual void execute(GameField *gameField, Base *base, LogProxy *logger, Base *enemyBase) = 0;
};

#endif //OOP_COMMAND_H
