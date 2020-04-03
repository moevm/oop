#include "logadapter.h"

LogAdapter::LogAdapter(ILogger *logger)
    : logger(logger) {
    type = SHORT;
}

void LogAdapter::setLogger(ILogger *logger)
{
    if (this->logger != nullptr)
        delete this->logger;
    this->logger = logger;
}

void LogAdapter::pushLog(LogEvent event, std::vector<int> param)
{
    if (logger->isActive())
    {
        std::string output;
        if (event == GAME_CREATE)
            logger->printLog(makeGameCreateLog(param));
        else if (event == BASE_ADD)
            logger->printLog(makeBaseAddLog(param));
        else if (event == NEUTRAL_ADD)
            logger->printLog(makeNeutralAddLog(param));
        else if (event == UNIT_ADD)
            logger->printLog(makeUnitAddLog(param));
        else if (event == BASE_UPDATE)
            logger->printLog(makeBaseUpdateLog(param));
        else if (event == UNIT_ATTACK)
            logger->printLog(makeAttackLog(param));
        else if (event == UNIT_MOVE)
            logger->printLog(makeMoveLog(param));
        else if (event >= USER_GAME_INFO && event <= USER_ATTACK)
            logger->printLog(makeUserActionLog(event, param));
    }
}

std::string LogAdapter::makeBaseAddLog(std::vector<int> param)
{
    if (param.size() < 4)
        throw std::out_of_range("Error! Wrong parameters for base add log");
    std::string output;
    output += "Created: BASE at coords: X=" + std::to_string(param[1]) + " Y=" + std::to_string(param[2]);
    output += " | game bases number: " + std::to_string(param[0]);
    output += "\n\t\t | Update: field item counter: " + std::to_string(param[3]);
    return output;
}

std::string LogAdapter::makeNeutralAddLog(std::vector<int> param)
{
    if (param.size() < 4)
        throw std::out_of_range("Error! Wrong parameters for neutral add log");
    std::string output;
    if (type == SHORT)
    {
        std::vector<std::string> shortNames = {"CHEST", "KEYG", "ANTIV", "DATA"};
        output += "Created: neutral " + shortNames[static_cast<unsigned>(param[0]-CHEST)];
        param = {param[3]};
        output += makeCounterUpdate(param);
    }
    else
    {
        std::vector<std::string> names = {"CHEST", "KEYGEN", "ANTIVIRUS", "DATA"};
        output += "Created: neutral " + names[static_cast<unsigned>(param[0]-CHEST)];
        output += " | coords: X=" + std::to_string(param[1]) + " Y=" + std::to_string(param[2]);
        param = {param[3]};
        output += "\n\t\t | " + makeCounterUpdate(param);
    }
    return output;
}

std::string LogAdapter::makeUnitAddLog(std::vector<int> param)
{
    if (param.size() < 4)
        throw std::out_of_range("Error! Wrong parameters for unit add log");
    std::string output;
    if (type == SHORT)
    {
         std::vector<std::string> shortNames = {"ATT_SC", "ATT_BS", "SUP_SC", "SUP_BS", "SIM_SC", "SIM_BS"};
         output += "Created: unit " + shortNames[static_cast<unsigned>(param[0])];
         output += " | base: N=" + std::to_string(param[1]);
    }
    else
    {
        std::vector<std::string> names = {"ATTACK SCIENTIST", "ATTACK BERSERK", "SUPPORT SCIENTIST",
                                          "SUPPORT BERSERK", "SIMPLE SCIENTIST", "SIMPLE BERSERK"};
        output += "Created: unit " + names[static_cast<unsigned>(param[0])];
        output += " | coords: X=" + std::to_string(param[2]) + " Y=" + std::to_string(param[3]);
        output += " | base: number=" + std::to_string(param[1]);
    }
    return output;
}

std::string LogAdapter::makeBaseUpdateLog(std::vector<int> param)
{
    if (param.size() < 5)
        throw std::out_of_range("Error! Wrong parameters for base update log");
    std::string output;
    if (type == SHORT)
    {
        output = "Update: BASE | coords: X=" + std::to_string(param[0]) + " Y=" + std::to_string(param[1]);
        output += " | uc: " + std::to_string(param[3]) + " | ul: " + std::to_string(param[4]);
    }
    else
    {
        std::vector<std::string> shortNames = {"ATT_SC", "ATT_BS", "SUP_SC", "SUP_BS", "SIM_SC", "SIM_BS"};
        output = "Update: BASE | coords: X=" + std::to_string(param[0]) + " Y=" + std::to_string(param[1]);
        output += " | unit counter: " + std::to_string(param[3]) + " | unit limit: " + std::to_string(param[4]);
        output += "\n\t\t | units: ";
        for (unsigned i=5; i<param.size(); i++)
        {
            output += shortNames[static_cast<unsigned>(param[i])] + " ";
        }
    }
    return output;
}

std::string LogAdapter::makeAttackLog(std::vector<int> param)
{
    if (param.size() < 6)
        throw std::out_of_range("Error! Wrong parameters for attack log");
    std::vector<std::string> shortNames = {"ATT_SC", "ATT_BS", "SUP_SC", "SUP_BS", "SIM_SC", "SIM_BS"};
    std::string output;
    output += "Attacked: FROM unit " + shortNames[static_cast<unsigned>(param[5])] + " | coords: X=" + std::to_string(param[0]) + " Y=" + std::to_string(param[1]);
    output += " | TO coords: X=" + std::to_string(param[2] + param[0]) + " Y=" + std::to_string(param[3] + param[1]);
    if (!param[4])
    {
        output += " | KILLED";
        param = {param[6]};
        output += "\n\t\t | " + makeCounterUpdate(param);
    }
    return output;
}

std::string LogAdapter::makeCounterUpdate(std::vector<int> param)
{
    std::string output;
    output += "Update: field item counter: " + std::to_string(param[0]);
    return output;
}

std::string LogAdapter::makeMoveLog(std::vector<int> param)
{
    if (param.size() < 5)
        throw std::out_of_range("Error! Wrong parameters for create game log");
    std::vector<std::string> shortNames = {"ATT_SC", "ATT_BS", "SUP_SC", "SUP_BS", "SIM_SC", "SIM_BS"};
    std::string output;
    output += "Moved: unit " + shortNames[static_cast<unsigned>(param[4])];
    if (type == FULL)
    {
        output += " | FROM: X=" + std::to_string(param[0]) + " Y= " + std::to_string(param[1]);
        output += " | BY: X=" + std::to_string(param[2]) + " Y= " + std::to_string(param[3]);
    }
    return output;
}

std::string LogAdapter::makeGameCreateLog(std::vector<int> param)
{
    if (param.size() < 4)
        throw std::out_of_range("Error! Wrong parameters for create game log");
    std::string output;
    if (type == SHORT)
    {
        output += "Created: GAME with FIELD | size: W=" + std::to_string(param[0]) + " H=" + std::to_string(param[1]);
        output += " | il: " + std::to_string(param[3]);
    }
    else
    {
        output += "Created: GAME with FIELD | size: width=" + std::to_string(param[0]) + " height=" + std::to_string(param[1]);
        output += " | item limit: " + std::to_string(param[3]);
    }
    return output;
}

std::string LogAdapter::makeUserActionLog(LogEvent event, std::vector<int> param)
{
    std::string output;
    switch (event) {
    case USER_BASE_INFO:
        output += "USER | Request: base info";
        break;
    case USER_GAME_INFO:
        output += "USER | Request: game info";
        break;
    case USER_LAND_INFO:
        output += "USER | Request: land info";
        break;
    case USER_ITEMS_INFO:
        output += "USER | Request: items info";
        break;
    case USER_ITEM_INFO:
        output += "USER | Request: item by XY info";
        break;
    case USER_BASE_ADD:
        output += "USER | Request: create new base";
        break;
    case USER_UNIT_ADD:
        output += "USER | Request: create unit";
        break;
    case USER_NEUTRAL_ADD:
        output += "USER | Request: create neutral";
        break;
    case USER_MOVE:
        output += "USER | Request: move unit";
        break;
    case USER_ATTACK:
        output += "USER | Request: attack unit";
        break;
    }
    return output;
}

LogType LogAdapter::getType() const
{
    return type;
}

void LogAdapter::setType(const LogType &value)
{
    type = value;
}

LogAdapter::~LogAdapter()
{
    delete logger;
}

