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

void MementoWriter::write(std::shared_ptr<GameParametersMemento> memento)
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

void MementoWriter::writeFieldProxy(std::shared_ptr<FieldProxyParametersMemento>& memento)
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

void MementoWriter::writeField(std::shared_ptr<FieldParametersMemento>& memento)
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

void MementoWriter::writeUnit(std::shared_ptr<UnitParametersMemento> memento)
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

MementoReader::MementoReader(std::string fileName_) : fileName(fileName_) { };

std::shared_ptr<GameParametersMemento> MementoReader::read()
{
    file.open(fileName, std::ifstream::in);
    std::shared_ptr<GameParametersMemento> memento = std::make_shared<GameParametersMemento>();

    std::string checkStr;
    int checkNumb;
    int x, y;

    std::getline(file, checkStr);
    if(checkStr != "!--GAME SAVE--!") throw std::runtime_error("Invalid save file title");

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 1) throw std::runtime_error("Invalid count of units");
    memento->playersCount = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid count of elements of base names dict");
    for(int i = 0; i < checkNumb; ++i)
    {
        file >> checkStr >> x >> y;
        if(x < 0 || y < 0) throw std::runtime_error("Invalid coords of base (name reading)");
        memento->baseNames.insert(std::pair(checkStr, Coords(x, y)));
        // EMPTY LINE AFTER >>
        std::getline(file, checkStr);
    }

    memento->fieldParam = readFieldProxyPar();

    return memento;
}

std::shared_ptr<FieldProxyParametersMemento> MementoReader::readFieldProxyPar()
{
    std::shared_ptr<FieldProxyParametersMemento> memento = std::make_shared<FieldProxyParametersMemento>();

    std::string checkStr;
    int checkNumb;
    int x, y;

    std::getline(file, checkStr);
    if(checkStr != "!--FIELD_PROXY--!") throw std::runtime_error("Invalid fileds proxy par title");

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid count of elements of landscape el in dict");
    for(int i = 0; i < checkNumb; ++i)
    {
        file >> x >> y >> checkStr;
        if(x < 0 || y < 0) throw std::runtime_error("Invalid coords of landscape");
        memento->landscape.insert(std::pair(Coords(x, y), checkStr));
        // EMPTY LINE AFTER >>
        std::getline(file, checkStr);
    }

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid count of neutral elements in dict");
    for(int i = 0; i < checkNumb; ++i)
    {
        file >> x >> y >> checkStr;
        if(x < 0 || y < 0) throw std::runtime_error("Invalid coords of neutral object");
        memento->neutralObjects.insert(std::pair(Coords(x, y), checkStr));
        // EMPTY LINE AFTER >>
        std::getline(file, checkStr);
    }

    memento->fieldParam = readFieldPar();

    return memento;
}

std::shared_ptr<FieldParametersMemento> MementoReader::readFieldPar()
{
    std::shared_ptr<FieldParametersMemento> memento = std::make_shared<FieldParametersMemento>();

    std::string checkStr;
    int checkNumb;
    int x, y;

    std::getline(file, checkStr);
    if(checkStr != "!--FIELD--!") throw std::runtime_error("Invalid field par title");

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid count of units");
    memento->unitsCount = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0 || static_cast<size_t>(checkNumb) < memento->unitsCount) throw std::runtime_error("Invalid max count of units");
    memento->maxUnitsCount = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid count of bases");
    memento->baseCount = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0 || static_cast<size_t>(checkNumb) < memento->baseCount) throw std::runtime_error("Invalid max count of bases");
    memento->maxBaseCount = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid field width");
    memento->width = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid field height");
    memento->height = checkNumb;

    std::getline(file, checkStr);
    if(checkStr != "!--BASES--!") throw std::runtime_error("Invalid bases par title");
    std::getline(file, checkStr);
    if(checkStr != "{") throw std::runtime_error("Ivalid bases block");
    for(size_t i = 0; i < memento->baseCount; ++i)
    {
        file >> x >> y;
        memento->bases.insert(std::pair(Coords(x, y), readBasePar()));
    }

    std::getline(file, checkStr);
    if(checkStr != "}") throw std::runtime_error("Ivalid bases block");

    std::getline(file, checkStr);
    if(checkStr != "!--UNITS--!") throw std::runtime_error("Invalid units par title");
    std::getline(file, checkStr);
    if(checkStr != "{") throw std::runtime_error("Ivalid units block");
    for(size_t i = 0; i < memento->unitsCount; ++i)
    {
        file >> x >> y;
        memento->units.insert(std::pair(Coords(x, y), readUnitPar()));
    }

    std::getline(file, checkStr);
    if(checkStr != "}") throw std::runtime_error("Ivalid units block");

    return memento;
}

std::shared_ptr<BaseParametersCaretaker> MementoReader::readBasePar()
{
    std::shared_ptr<BaseParametersCaretaker> memento = std::make_shared<BaseParametersCaretaker>();

    std::string checkStr;
    int checkNumb;

    // EMPTY LINE AFTER >>
    std::getline(file, checkStr);

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid base health");
    memento->health = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid base health");
    memento->type = static_cast<eBaseType>(checkNumb);

    memento->unitCountsData = readUnitCountsData();

    return memento;
}

std::shared_ptr<UnitStorekeeperParametersMemento> MementoReader::readUnitCountsData()
{
    std::shared_ptr<UnitStorekeeperParametersMemento> memento = std::make_shared<UnitStorekeeperParametersMemento>();

    std::string checkStr;

    for(size_t i = 0; i < TYPES_OF_UNIT; ++i)
    {
        std::getline(file, checkStr);
        memento->unitAccountingInf.push_back(checkStr);
    }

    return memento;
}

std::shared_ptr<UnitParametersMemento> MementoReader::readUnitPar()
{
    std::shared_ptr<UnitParametersMemento> memento = std::make_shared<UnitParametersMemento>();

    std::string checkStr;
    int checkNumb;
    int x, y;

    // EMPTY LINE AFTER >>
    std::getline(file, checkStr);

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0 || checkNumb > TYPES_OF_UNIT) throw std::runtime_error("Invalid unit type");
    memento->type = static_cast<eUnitsType>(checkNumb);

    std::getline(file, checkStr);
    memento->name = checkStr;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid unit health");
    memento->health = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid unit armor");
    memento->armor = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid unit melee attack strength");
    memento->meleeAttackStrength = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid unit movement range");
    memento->movementRange = checkNumb;

    std::getline(file, checkStr);
    checkNumb = std::stoi(checkStr);
    if(checkNumb < 0) throw std::runtime_error("Invalid unit action tokens");
    memento->actionTokens = checkNumb;

    file >> x >> y;
    memento->position = Coords(x, y);

    // EMPTY LINE AFTER >>
    std::getline(file, checkStr);

    file >> x >> y;
    memento->creationBaseCoords = Coords(x, y);

    // EMPTY LINE AFTER >>
    std::getline(file, checkStr);

    return memento;
}

MementoReader::~MementoReader()
{
    file.close();
}
