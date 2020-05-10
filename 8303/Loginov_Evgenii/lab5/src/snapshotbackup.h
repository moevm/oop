#ifndef SNAPSHOTBACKUP_H
#define SNAPSHOTBACKUP_H

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
    Base *base;
    FileRAII *fileWrie;
    FileRead *fileRead;
    Adapter* adapter;

public:
    SnapshotBackup(Field* field, int x, int y, int maxUnit, int curUnit, Base* base);
    SnapshotBackup(Field *field);
    ~SnapshotBackup();

    void saveGame();
    void loadGame();

};

#endif // SNAPSHOTBACKUP_H
