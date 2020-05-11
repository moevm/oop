#include "mementofiles.h"

#include <iostream>

MementoWriter::MementoWriter(std::string name)
{
    file.open(name, std::ofstream::trunc);
}

MementoWriter::~MementoWriter()
{
    file.close();
}

void MementoWriter::write(std::shared_ptr<GameParametersCaretaker> memento)
{
    file << "!--GAME SAVE--!" << std::endl;
    file << memento->playersCount << std::endl;

    file << memento->baseNames.size() << std::endl;
    for(const auto& curr : memento->baseNames)
    {
        file << curr.first << " " << curr.second.x << " "<< curr.second.y << std::endl;
    }

    writeFieldProxy(memento->fieldParam);
}

void MementoWriter::writeFieldProxy(std::shared_ptr<FieldProxyParametersCaretaker>& memento)
{
    file << "!--FIELD_PROXY--!" << std::endl;
    file << memento->landscape.size() << std::endl;
    for(const auto& curr : memento->landscape)
    {
        file << curr.first.x << " " << curr.first.y << " " << curr.second << std::endl;
    }
    file << memento->neutralObjects.size() << std::endl;
    for(const auto& curr : memento->neutralObjects)
    {
        file << curr.first.x << " " << curr.first.y << " " << curr.second << std::endl;
    }

    writeField(memento->fieldParam);
}

void MementoWriter::writeField(std::shared_ptr<FieldParametersCaretaker>& memento)
{
    file << "!--FIELD--!" << std::endl;
    file << memento->unitsCount << std::endl;
    file << memento->maxUnitsCount << std::endl;
    file << memento->baseCount << std::endl;
    file << memento->maxBaseCount << std::endl;
    file << memento->width << std::endl;
    file << memento->height << std::endl;

    file << "!--BASES--!" << std::endl;
    file << "{" << std::endl;
    for(const auto& curr : memento->bases)
    {
        file << curr.first.x << " " << curr.first.y << std::endl;
        writeBase(curr.second);
    }
    file << "}" << std::endl;

    file << "!--UNITS--!" << std::endl;
    file << "{" << std::endl;
    for(const auto& curr : memento->units)
    {
        file << curr.first.x << " " << curr.first.y << std::endl;
        writeUnit(curr.second);
    }
    file << "}" << std::endl;
}

void MementoWriter::writeBase(std::shared_ptr<BaseParametersCaretaker> memento)
{
    file << memento->health << std::endl;
    file << memento->type << std::endl;
    for(const auto& curr : memento->unitCountsData->unitAccountingInf)
    {
        file << curr << std::endl;
    }
}

void MementoWriter::writeUnit(std::shared_ptr<UnitParametersCaretaker> memento)
{
    file << memento->type << std::endl;
    file << memento->name << std::endl;
    file << memento->health << std::endl;
    file << memento->armor << std::endl;
    file << memento->meleeAttackStrength << std::endl;
    file << memento->movementRange << std::endl;
    file << memento->actionTokens << std::endl;
    file << memento->position.x << " " << memento->position.y << std::endl;
    file << memento->creationBaseCoords.x << " " << memento->creationBaseCoords.y << std::endl;
}

MementoReader::MementoReader(std::string name)
{
}

GameParametersCaretaker MementoReader::read()
{

}

MementoReader::~MementoReader()
{

}
