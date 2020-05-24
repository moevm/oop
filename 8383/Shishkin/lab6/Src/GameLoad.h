#pragma once

#include "SnapshotGame.h"
#include "Landscape.h"
#include "NeutralObject.h"
#include <fstream>

class GameLoad {
public:
    GameLoad(string name);
    ~GameLoad();
    SnapshotGame* load();
private:
    ifstream file;
    string fileName;
};