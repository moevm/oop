#ifndef GAMEMEMENTO_H
#define GAMEMEMENTO_H

#include "ICaretacker.h"
#include "SaveStuctures.h"
#include "mementofiles.h"

class GameMementoCaretacker : public ICaretacker
{
public:
    GameMementoCaretacker() = default;
    std::shared_ptr<GameParametersMemento> loadFromFile(std::string fileName) override;
    void saveToFile(std::string fileName, std::shared_ptr<Game> game_) override;

private:
    std::shared_ptr<Game> game{};
    std::string workFileName{};
};

#endif // GAMEMEMENTO_H
