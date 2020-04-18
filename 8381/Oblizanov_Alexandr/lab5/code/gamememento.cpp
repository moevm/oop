#include "gamememento.h"


GameMemento::GameMemento(std::string name, GameParameters param)
    : name(name), param(param)
{
    MementoWriter fout(name);
    fout.write(param);
}

GameMemento::GameMemento(std::string name)
    : name(name) {}

GameParameters GameMemento::loadFromFile()
{
    MementoReader fin(name);
    return fin.read();
}

MementoReader::MementoReader(std::string name)
    : name(name)
{
    file.open(name + ".cyb");
    if (!file.is_open())
        throw std::runtime_error("File open for read failure");
}

MementoWriter::MementoWriter(std::string name)
    : name(name)
{
    file.open(name + ".cyb");
    if (!file.is_open())
        throw std::runtime_error("File open for write failure");
}

void MementoWriter::write(GameParameters param)
{
    //field info write
    file << name << "\nFIELD\n";
    file << param.width << " " << param.height << " " << param.itemLimit << " " << param.itemCounter;
    unsigned fieldSize = param.height*param.width;
    //landscape info write
    file << "\nLAND\n";
    for (unsigned i=0; i<fieldSize; i++)
    {
        file << param.landscape[i] << " ";
    }
    //bases and units info write
    file << "\nBASES\n";
    file << param.baseCount << "\n";
    for (auto i : param.bases)
    {
        file << i.number << " " << i.x << " " << i.y << " " << i.limit << " " << i.stability << "\n";
        file << i.units.size() << "\n";
        for (auto j : i.units)
        {
            file << j.x << " " << j.y << " " << j.type << " ";
            file << j.move << " " << j.power << " " << j.spread << " ";
            file << j.charactBonus << " " << j.attackBonus << " " << j.securityBonus << "\n";
        }
    }
    //neutrals info write
    file << "NEUTRALS\n";
    file << param.neutrals.size() << "\n";
    for (auto i : param.neutrals)
    {
        file << i.x << " " << i.y << " " << i.type << "\n";
    }
}

GameParameters MementoReader::read()
{
    GameParameters param;
    unsigned tempInt = 0;
    std::string tempStr;

    //getting field info
    file >> tempStr;
    if (tempStr != name)
        throw std::invalid_argument("File heading wrong");
    file >> tempStr;
    if (tempStr != "FIELD")
        throw std::invalid_argument("Field header wrong");
    file >> param.width >> param.height;
    file >> param.itemLimit >> param.itemCounter;

    //getting landscape info
    file >> tempStr;
    if (tempStr != "LAND")
        throw std::invalid_argument("Landscape header wrong");
    for (unsigned i=0; i<param.width*param.height; i++)
    {
        if (!(file >> tempInt))
            throw std::invalid_argument("Landscape parameters wrong");
        param.landscape.push_back(static_cast<LandType>(tempInt));
    }
    file >> tempStr;

    //getting bases and units info
    if (tempStr != "BASES")
        throw std::invalid_argument("Bases header wrong");
    file >> param.baseCount;
    for (unsigned i=0; i<param.baseCount; i++)
    {
        BaseParameters bParam;
        file >> bParam.number >> bParam.x >> bParam.y >> bParam.limit >> bParam.stability;
        file >> tempInt;
        for (unsigned i=0; i<tempInt; i++)
        {
            unsigned type;
            UnitParameters uParam;
            file >> uParam.x >> uParam.y >> type;
            file >> uParam.move >> uParam.power >> uParam.spread;
            file >> uParam.charactBonus >> uParam.attackBonus >> uParam.securityBonus;
            uParam.type = static_cast<UnitType>(type);
            bParam.units.push_back(uParam);
        }
        param.bases.push_back(bParam);
    }

    //getting neutrals info
    file >> tempStr;
    if (tempStr != "NEUTRALS")
        throw std::invalid_argument("Neutrals header wrong");
    file >> tempInt;
    for (unsigned i=0; i<tempInt; i++)
    {
        unsigned type;
        NeutralParameters nParam;
        if (!(file >> nParam.x >> nParam.y >> type))
            throw std::invalid_argument("Neutral parameters wrong");
        nParam.type = static_cast<NeutralType>(type);
        param.neutrals.push_back(nParam);
    }
    //to file beginning
    file.clear();
    file.seekg(0);
    return param;
}

MementoReader::~MementoReader()
{
    if (file.is_open())
        file.close();
}

MementoWriter::~MementoWriter()
{
    if (file.is_open())
        file.close();
}
