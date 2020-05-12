#ifndef MEMENTOFILES_H
#define MEMENTOFILES_H

#include <string>
#include <fstream>
#include <exception>
#include <regex>

#include "SaveStuctures.h"

class MementoReader
{
public:
    MementoReader(std::string fileName_);
    std::shared_ptr<GameParametersMemento> read();
    ~MementoReader();
private:
    std::ifstream file;
    std::string fileName;

    std::shared_ptr<FieldProxyParametersMemento> readFieldProxyPar();
    std::shared_ptr<FieldParametersMemento> readFieldPar();
    std::shared_ptr<BaseParametersCaretaker> readBasePar();
    std::shared_ptr<UnitStorekeeperParametersMemento> readUnitCountsData();
    std::shared_ptr<UnitParametersMemento> readUnitPar();
};

class MementoWriter
{
public:
    MementoWriter(std::string fileName);
    void write(std::shared_ptr<GameParametersMemento> memento);
    ~MementoWriter();
private:
    std::ofstream file;
    std::string fileName;

    void writeFieldProxy(std::shared_ptr<FieldProxyParametersMemento>& memento);
    void writeField(std::shared_ptr<FieldParametersMemento>& memento);
    void writeBase(std::shared_ptr<BaseParametersCaretaker> memento);
    void writeUnit(std::shared_ptr<UnitParametersMemento> memento);
};

#endif // MEMENTOFILES_H
