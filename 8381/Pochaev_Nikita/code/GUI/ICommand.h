#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <vector>

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual std::vector<size_t> exec() = 0;
};

#endif // ICOMMAND_H
