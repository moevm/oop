#pragma once

#include "Snapshot/SnapshotGame.h"
#include "Snapshot/GameSave.h"
#include "Snapshot/GameLoad.h"
#include <string>

using namespace std;

class CommandMemento {
public:
    virtual ~CommandMemento() = default;
    virtual SnapshotGame* loadFromFile() = 0;
};

class GameMemento : public CommandMemento
{
public:
    GameMemento(string name, SnapshotGame* snapshot);
    GameMemento(string name);
    SnapshotGame* loadFromFile();
private:
    string fileName;
    SnapshotGame* snapshot;
};
