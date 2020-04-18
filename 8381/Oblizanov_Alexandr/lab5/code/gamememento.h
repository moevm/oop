#ifndef GAMEMEMENTO_H
#define GAMEMEMENTO_H

#include "attackmediator.h"

class MementoReader
{
public:
    MementoReader(std::string name);
    GameParameters read();
    ~MementoReader();
private:
    std::ifstream file;
    std::string name;
};

class MementoWriter
{
public:
    MementoWriter(std::string name);
    void write(GameParameters param);
    ~MementoWriter();
private:
    std::ofstream file;
    std::string name;
};

class GameMemento : public IMemento
{
public:
    GameMemento(std::string name, GameParameters param);
    GameMemento(std::string name);
    GameParameters loadFromFile();
private:
    std::string name;
    GameParameters param;
};

#endif // GAMEMEMENTO_H
