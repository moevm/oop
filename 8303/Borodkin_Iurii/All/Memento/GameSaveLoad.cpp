#include "GameSaveLoad.h"

GameSaveLoad::GameSaveLoad(std::string path, Memento s) : saveFile(path), state(s)
{
}

void GameSaveLoad::save()
{

    if (!saveFile.is_open())
        throw InvalidFielLoadingException();

    std::unordered_map <Object*, bool> isSaved;
    isSaved[nullptr] = true;
    auto field = state.getState();
    switch (field->height())
    {
        case 10:
        {
            saveFile << "[size] = 10x10" << std::endl;
            break;
        }
        case 15:
        {
            saveFile << "[size] = 15x15" << std::endl;
            break;
        }
    }

    switch (field->countPlayers)
    {
        case 2:
        {
            saveFile << "[count_players] = 2" << std::endl;
            break;
        }
        case 3:
        {
            saveFile << "[count_players] = 3" << std::endl;
            break;
        }
    }

    for (int i = 0; i < int(field->height()); i++)
    {
        for (int j = 0; j < int(field->width()); j++)
        {
            auto c = field->at({i, j});
            if (!isSaved[c.obj] || c.pack)
                saveFile << "[" << i << "]" << "[" << j << "]" << std::endl;

            if (c.obj && !isSaved[c.obj])
            {
                isSaved[c.obj] = true;

                saveFile << "\"" << c.obj->type() << "\"" << std::endl;
                saveFile << "Player: " << c.obj->player << std::endl;
                saveFile << "Hp: " << c.obj->health() << std::endl;

                if (c.obj->type() == "Base") {

                    saveFile << "Units:" << std::endl;
                    auto units = dynamic_cast<Base*>(c.obj)->getHeap().getUnits();
                    for (auto unit : units)
                        saveFile << unit->type() << std::endl;
                    saveFile << "End" << std::endl;

                } else {

                    saveFile << "Armor: " << c.obj->armor() << std::endl;
                    saveFile << "Damage: " << c.obj->damage() << std::endl;
                    saveFile << "Mana: " << c.obj->mana() << std::endl;

                }
            }

            if (c.pack)
                saveFile << "[Pack] = " << c.pack->type() << std::endl;
        }
    }

    saveFile << "EOF\n";
}

std::pair <std::pair<size_t, size_t>, bool> GameSaveLoad::getCoords(string& str)
{
    std::pair <std::pair<size_t, size_t>, bool> fail = {{}, false};

    if (str[0] != '[' || str[str.size()-1] != ']')
        return fail;

    size_t lastOpen = 0;
    int _i, _j;
    string digit;

    for (size_t i = 1; i < str.size(); i++)
    {
        if (i==lastOpen+1 && str[i] == ']')
            return fail;

        if (str[i] != ']' && !isdigit(str[i]))
            return fail;

        if (str[i] != ']') {
            digit += str[i];
        } else if (!lastOpen) {
            try {
                _i = std::stoi(digit);
            } catch (std::invalid_argument) {
                return fail;
            }

            digit.clear();
            if (i == str.size() - 1 || str[i+1] != '[')
                return fail;
            i++;
            lastOpen = i;
        } else if (i == str.size() - 1) {
            try {
                _j = std::stoi(digit);
            } catch (std::invalid_argument) {
                return fail;
            }
        } else
            return fail;
    }

    return {{_i, _j}, true};
}

bool GameSaveLoad::emplaceBase(Memento &newState, std::pair<size_t, size_t> coords, unsigned maxNumUnitsBase)
{
    string str;
    saveFile >> str;
    if (str != "Player:")
        return false;

    saveFile >> str;
    for (auto c : str)
        if (!isdigit(c))
            return false;

    unsigned player;

    try {
        player = std::stoul(str);
    } catch (std::invalid_argument) {
        return false;
    }

    saveFile >> str;
    if (str != "Hp:")
        return false;

    saveFile >> str;
    for (auto c : str)
        if (!isdigit(c))
            return false;

    unsigned hp;
    try {
        hp = std::stoul(str);
    } catch (std::invalid_argument) {
        return false;
    }

    newState.getState()->addBase(new Base("", maxNumUnitsBase, player), coords);
    (*newState.getState())[coords.first][coords.second].obj->getDamage(unsigned(int(HpTypes::BASE) - hp));

    saveFile >> str;
    if (str != "Units:")
        return false;

    saveFile >> str;
    while (str != "End")
    {
       if (str == "Wizard")
           (*newState.getState())[coords.first][coords.second].obj->createUnit(new Wizard(player));
       else if (str == "Archer")
           (*newState.getState())[coords.first][coords.second].obj->createUnit(new Archer(player));
       else if (str == "SwordsMan")
           (*newState.getState())[coords.first][coords.second].obj->createUnit(new SwordsMan(player));
       else if (str == "SpearMan")
           (*newState.getState())[coords.first][coords.second].obj->createUnit(new SpearMan(player));
       else if (str == "Centaur")
           (*newState.getState())[coords.first][coords.second].obj->createUnit(new Centaur(player));
       else if (str == "Panzer")
           (*newState.getState())[coords.first][coords.second].obj->createUnit(new Panzer(player));
       else return false;

        saveFile >> str;
    }

    return true;
}

std::pair<Attributes*, bool> GameSaveLoad::getAttributes()
{
    string str;
    std::pair<Attributes*, bool> fail = {nullptr, false};
    Attributes *attr = new Attributes(0,0,0,0,0);

    saveFile >> str;
    if (str != "Hp:")
        return fail;

    saveFile >> str;
    for (auto c : str)
        if (!isdigit(c))
            return fail;

    try {
        attr->health = std::stoi(str);
    } catch (std::invalid_argument) {
        return fail;
    }

    saveFile >> str;
    if (str != "Armor:")
        return fail;

    saveFile >> str;
    for (auto c : str)
        if (!isdigit(c))
            return fail;

    try {
        attr->armor = std::stoul(str);
    } catch (std::invalid_argument) {
        return fail;
    }
    saveFile >> str;
    if (str != "Damage:")
        return fail;

    saveFile >> str;
    for (auto c : str)
        if (!isdigit(c))
            return fail;

    try {
        attr->damage = std::stoul(str);
    } catch (std::invalid_argument) {
        return fail;
    }

    saveFile >> str;
    if (str != "Mana:")
        return fail;

    saveFile >> str;
    for (auto c :str)
        if (!isdigit(c))
            return fail;
    try {
        attr->mana = std::stoul(str);
    } catch (std::invalid_argument) {
        return fail;
    }
    return {attr, true};
}

std::pair <Memento, bool> GameSaveLoad::load()
{
    string str;
    std::pair <Memento, bool> fail = {Memento(nullptr), false};

    //"size"
    saveFile >> str;
    if (str != "[size]")
        return fail;

    saveFile >> str;
    if (str != "=")
        return fail;

    saveFile >> str;

    unsigned size = 0;
    if (str == "10x10")
        size = 10;
    else if (str == "15x15")
        size = 15;
    else
        return fail;


    // "Players"
    saveFile >> str;
    if (str != "[count_players]")
        return fail;

    saveFile >> str;
    if (str != "=")
        return fail;

    saveFile >> str;

    int count_players;
    try {
        count_players = std::stoi(str);
    } catch (std::invalid_argument) {
        return fail;
    }

    if (count_players < 0)
        return fail;

    Memento newState(nullptr);
    switch (count_players)
    {
        case 2:
        {
            if (size == 10) {

               newState.game1 = new Game<Rule1, Players2>(newState.getState());

            } else if (size == 15) {
                Game <Rule2, Players2>* game2;
                newState.game2 = new Game<Rule2, Players2>(newState.getState());
            }
            break;
        }
        case 3:
        {
            if (size == 10) {
                Game <Rule1, Players3>* game3;
                newState.game3 = new Game<Rule1, Players3>(newState.getState());
            } else if (size == 15) {
                Game <Rule2, Players3>* game4;
                newState.game4 = new Game<Rule2, Players3>(newState.getState());
            }
            break;
        }
        default:
            return fail;
    }


    while (str != "EOF")
    {
        saveFile >> str;
        if (str == "EOF")
            break;

        auto res = getCoords(str);
        if (!res.second || res.first.first >= newState.getState()->height() || res.first.second >= newState.getState()->height())
        {
            delete newState.getState();
            return fail;
        }

        auto coords = res.first;
        saveFile >> str;
        if (str == "\"Base\"")
        {
            if (!emplaceBase(newState, res.first, unsigned(newState.getState()->maxNumUnitsBase))) {
                delete newState.getState();
                return fail;
            }
            continue;
        } else if (str == "[Pack]") {

            saveFile >> str;
            if (str != "=")
            {
                delete newState.getState();
                return fail;
            }

            saveFile >> str;
            if (str == "Damage") {
                (*newState.getState())[coords.first][coords.second].pack = new DamagePack;
            } else if (str == "Mana") {
                (*newState.getState())[coords.first][coords.second].pack = new ManaPack;
            } else if (str == "Armor") {
                (*newState.getState())[coords.first][coords.second].pack = new ArmorPack;
            } else if (str == "Health") {
                (*newState.getState())[coords.first][coords.second].pack = new HealthPack;
            } else {
                delete newState.getState();
                return fail;
            }

        } else {

            string type = str;
            type = str;

            saveFile >> str;
            if (str != "Player:")
                return fail;

            saveFile >> str;
            for (auto c : str)
                if (!isdigit(c))
                    return fail;

            unsigned player;
            try {
                player = std::stoul(str);
            } catch (std::invalid_argument) {
                return fail;
            }

            auto res = getAttributes();
            if (!res.second)
            {
                delete newState.getState();
                return fail;
            }

            str = type;
            if (str == "\"Wizard\"") {
                res.first->range = unsigned(RngTypes::WIZARD);
                (*newState.getState())[coords.first][coords.second].obj = new Wizard(res.first, player);
            } else if (str == "\"Archer\"") {
                res.first->range = unsigned(RngTypes::ARCHER);
                (*newState.getState())[coords.first][coords.second].obj = new Archer(res.first, player);
            } else if (str == "\"SwordsMan\"") {
                res.first->range = unsigned(RngTypes::SWORDSMAN);
                (*newState.getState())[coords.first][coords.second].obj = new SwordsMan(res.first, player);
            } else if (str == "\"SpearMan\"") {
                res.first->range = unsigned(RngTypes::SPEARMAN);
                (*newState.getState())[coords.first][coords.second].obj = new SpearMan(res.first, player);
            } else if (str == "\"Centaur\"") {
                res.first->range = unsigned(RngTypes::CENTAUR);
                (*newState.getState())[coords.first][coords.second].obj = new Centaur(res.first, player);
            } else if (str == "\"Panzer\"") {
                res.first->range = unsigned(RngTypes::PANZER);
                (*newState.getState())[coords.first][coords.second].obj = new Panzer(res.first, player);
            } else {
                delete newState.getState();
                return fail;
            }

        }
    }

    state = newState;

    return {state, true};
}

GameSaveLoad::~GameSaveLoad()
{
    saveFile.close();
}
