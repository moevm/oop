#ifndef SNAPSHOTBACKUP_H
#define SNAPSHOTBACKUP_H

#include <vector>

class Field;
class FileRAII;
class FileRead;
class Base;
class Adapter;

class SnapshotBackup
{
private:
    int x, y;
    int maxUnit;
    int curUnit;
    Field *field;
    std::vector<Base*> bases;
    FileRAII *fileWrie;
    FileRead *fileRead;
    Adapter* adapter;

public:
    SnapshotBackup(Field* field, int x, int y, int maxUnit, int curUnit, std::vector<Base *> bases);
    SnapshotBackup(Field *field);
    ~SnapshotBackup();

    void saveGame();
    void loadGame();

    //files
};

#endif // SNAPSHOTBACKUP_H
