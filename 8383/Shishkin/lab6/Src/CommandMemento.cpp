#include "CommandMemento.h"

GameMemento::GameMemento(string name, SnapshotGame* params) : fileName(name), snapshot(params) {
    GameSave in(fileName);
    in.save(snapshot);
}

GameMemento::GameMemento(string name) : fileName(name), snapshot(nullptr) {

}

SnapshotGame* GameMemento::loadFromFile() {
    GameLoad out(fileName);
    return out.load();
}