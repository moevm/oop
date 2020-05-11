#ifndef MEMENTOFILES_H
#define MEMENTOFILES_H

#include <string>
#include <fstream>
#include "SaveStuctures.h"

class MementoReader
{
public:
    MementoReader(std::string name);
    GameParametersCaretaker read();
    ~MementoReader();
private:
    std::ifstream file;
    std::string fileName;
};

class MementoWriter
{
public:
    MementoWriter(std::string name);
    void write(std::shared_ptr<GameParametersCaretaker> memento);
    ~MementoWriter();
private:
    std::ofstream file;
    std::string name;

    void writeFieldProxy(std::shared_ptr<FieldProxyParametersCaretaker>& memento);
    void writeField(std::shared_ptr<FieldParametersCaretaker>& memento);
    void writeBase(std::shared_ptr<BaseParametersCaretaker> memento);
    void writeUnit(std::shared_ptr<UnitParametersCaretaker> memento);
};

#endif // MEMENTOFILES_H
