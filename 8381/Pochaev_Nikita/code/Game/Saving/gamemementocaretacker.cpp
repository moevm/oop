#include "gamemementocaretacker.h"

std::shared_ptr<GameParametersMemento> GameMementoCaretacker::loadFromFile(std::string fileName)
{
    game = nullptr;
    workFileName = fileName;

    MementoReader reader(workFileName);
    std::shared_ptr<GameParametersMemento> memento = reader.read();

    return memento;
}

void GameMementoCaretacker::saveToFile(std::string fileName, std::shared_ptr<Game> game_)
{
    game = std::move(game_);
    workFileName = fileName;

    MementoWriter writer(workFileName);
    std::shared_ptr<GameParametersMemento> memento = game->createMemento();
    writer.write(memento);
}
