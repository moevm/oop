#ifndef IMEMENTO_H
#define IMEMENTO_H

#include "SaveStuctures.h"
#include "Game/game.h"

class ICaretacker
{
public:
    virtual ~ICaretacker() = default;
    virtual std::shared_ptr<GameParametersMemento> loadFromFile(std::string fileName) = 0;
    virtual void saveToFile(std::string fileName, std::shared_ptr<Game> game_) = 0;
};

#endif // IMEMENTO_H
