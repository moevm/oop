#ifndef GAMESAVELOAD_H
#define GAMESAVELOAD_H

#include <fstream>
#include <unordered_map>
#include "Memento.h"
#include "Game.h"
#include "exceptions/invalidfielloadingexception.h"

class GameSaveLoad
{
    std::fstream saveFile;

public:
    explicit GameSaveLoad(std::string, Memento);
    void save();
    std::pair <Memento, bool> load();
    Memento state;
    ~GameSaveLoad();
private:
    std::pair <std::pair<size_t, size_t>, bool> getCoords(string&);
    bool emplaceBase(Memento&, std::pair<size_t, size_t>, unsigned);
    std::pair<Attributes*, bool> getAttributes();
};

#endif // GAMESAVELOAD_H
