#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <vector>
#include <string>

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void exec() = 0;
};

#endif // ICOMMAND_H
