#ifndef COMMANDSQUEUE_H
#define COMMANDSQUEUE_H

#include <queue>

class Command;
class Logger;

class CommandsQueue
{
    std::queue<Command*> commands;
    Logger *logger;

public:
//    CommandsQueue(Game &game);
    ~CommandsQueue();
    void push(Command* cmd);
    std::pair<int, int> apply(Logger *logger = nullptr);

    size_t size() const;
    bool empty() const;
};

#endif // COMMANDSQUEUE_H
