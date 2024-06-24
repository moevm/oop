#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include "field.h"
#include "infile.h"
class Snapshot
{
    Field* field;
    Base* alienbase;
    Base* humanbase;
    //ofstream filesave;
    //ifstream fileload;
public:
    Snapshot(Field* fieldd)
    {
        this->field = fieldd;
        this->alienbase = this->field->getABase();
        this->humanbase = this->field->getHBase();
        //this->filesave.open("GameSave.txt");
        //this->fileload.open("GameLoad.txt");
    }
    void saveGame();
    void loadGame();
    ~Snapshot()
    {
        //filesave.close();
        //fileload.close();
    }
};

#endif // SNAPSHOT_H
