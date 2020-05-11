#include "logadapter.h"

#include "Units/Unit.h"
#include "Bases/GameBase.h"
#include "GUI/command.h"

LogAdapter::LogAdapter(std::shared_ptr<ILogger> logger_) : logger(std::move(logger_)) { }

void LogAdapter::setLogger(std::shared_ptr<ILogger> logger_)
{
    logger = std::move(logger_);
}

void LogAdapter::setOutputFormat(eLOGGER_OUTPUT_FORMAT format_)
{
    format = format_;
}

/**
 * @brief LogAdapter::generateGameCreationLog
 * @param source
 * @param event
 * @param param
 * 1st - count of players
 * 2nd - field size
 * @return
 */
std::string LogAdapter::generateGameCreationLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText)
{
    if(param.size() < 2 && format == ADVANCED)
    {
        throw std::invalid_argument("Invalid number of parameters for logging the creation of the game");
    }

    std::string res = "";
    if(source == USER_LOG)
    {
        res += "USER : request for game creation";
    }
    else if(source == GAME_LOG)
    {
        res += "GAME : game creation";
    }

    if(format == ADVANCED)
    {
        res += " with " + std::to_string(param[0]) + " players on " + std::to_string(param[1]) + "*" + std::to_string(param[1]) + " field";
    }

    if(logger->getType() == TERMINAL_LOG)
    {
        if(suc == SUCCESS)
        {
            res += " | " + ANSIColor::coloredString("SUCCESS", ANSIColor::FG_GREEN);
        }
        else if(suc == WRONG)
        {
            res += " | " + ANSIColor::coloredString("WRONG", ANSIColor::FG_RED);
        }
    }
    else
    {
        if(suc == SUCCESS)
        {
            res += " | SUCCESS";
        }
        else if(suc == WRONG)
        {
            res += " | WRONG";
        }
    }

    if(format == ADVANCED && errorText.length() != 0)
    {
       res += (" => " + errorText);
    }

    return res;
}

/**
 * @brief LogAdapter::generateUnitAddLog
 * @param source
 * @param format
 * @param param
 * 1st - X coord of adding
 * 2nd - Y coord of adding
 * 3d - unit type
 * @return
 */
std::string LogAdapter::generateUnitAddLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText)
{
    if(param.size() < 3 && format == ADVANCED)
    {
        throw std::invalid_argument("Invalid number of parameters for logging the unit adding");
    }

    std::string res = "";
    if(source == USER_LOG)
    {
        res += "USER : request for unit add";
    }
    else if(source == GAME_LOG)
    {
        res += "GAME : unit adding";
    }

    if(format == ADVANCED)
    {
        res += " at (" + std::to_string(param[0]) + ";" + std::to_string(param[1]) + ") with type: " + Unit::convertEnumUnitNameToStr(static_cast<eUnitsType>(param[2]));
    }

    if(logger->getType() == TERMINAL_LOG)
    {
        if(suc == SUCCESS)
        {
            res += " | " + ANSIColor::coloredString("SUCCESS", ANSIColor::FG_GREEN);
        }
        else if(suc == WRONG)
        {
            res += " | " + ANSIColor::coloredString("WRONG", ANSIColor::FG_RED);
        }
    }
    else
    {
        if(suc == SUCCESS)
        {
            res += " | SUCCESS";
        }
        else if(suc == WRONG)
        {
            res += " | WRONG";
        }
    }

    if(format == ADVANCED && errorText.length() != 0)
    {
        res += (" => " + errorText);
    }

    return res;
}

/**
 * @brief LogAdapter::generateBaseAddLog
 * @param source
 * @param format
 * @param param
 * 1st - X coord of adding
 * 2nd - Y coord of adding
 * 3d - base type
 * @return
 */
std::string LogAdapter::generateBaseAddLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText)
{
    if(param.size() < 3 && format == ADVANCED)
    {
        throw std::invalid_argument("Invalid number of parameters for logging the base adding");
    }

    std::string res = "";
    if(source == USER_LOG)
    {
        res += "USER : request for base add";
    }
    else if(source == GAME_LOG)
    {
        res += "GAME : base adding";
    }

    if(format == ADVANCED)
    {
        res += " at (" + std::to_string(param[0]) + ";" + std::to_string(param[1]) + ") with type: " + GameBase::convertEnumBaseNameToStr(static_cast<eBaseType>(param[2]));
    }

    if(logger->getType() == TERMINAL_LOG)
    {
        if(suc == SUCCESS)
        {
            res += " | " + ANSIColor::coloredString("SUCCESS", ANSIColor::FG_GREEN);
        }
        else if(suc == WRONG)
        {
            res += " | " + ANSIColor::coloredString("WRONG", ANSIColor::FG_RED);
        }
    }
    else
    {
        if(suc == SUCCESS)
        {
            res += " | SUCCESS";
        }
        else if(suc == WRONG)
        {
            res += " | WRONG";
        }
    }


    if(format == ADVANCED && errorText.length() != 0)
    {
        res += (" => " + errorText);
    }

    return res;
}

/**
 * @brief LogAdapter::generateUnitAttackLog
 * @param source
 * @param format
 * @param param
 * 1st - X coord source
 * 2nd - Y coord source
 * 3d - X coord dest
 * 4th - Y coord dest
 * @return
 */
std::string LogAdapter::generateUnitAttackLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText)
{
    if(param.size() < 4 && format == ADVANCED)
    {
        throw std::invalid_argument("Invalid number of parameters for logging the unit attack");
    }

    std::string res = "";
    if(source == USER_LOG)
    {
        res += "USER : request for unit attack";
    }
    else if(source == GAME_LOG)
    {
        res += "GAME : unit attack";
    }

    if(format == ADVANCED)
    {
        res += " from (" + std::to_string(param[0]) + ";" + std::to_string(param[1]) + ") to (" + std::to_string(param[2]) + ";" + std::to_string(param[3]) + ")";
    }

    if(logger->getType() == TERMINAL_LOG)
    {
        if(suc == SUCCESS)
        {
            res += " | " + ANSIColor::coloredString("SUCCESS", ANSIColor::FG_GREEN);
        }
        else if(suc == WRONG)
        {
            res += " | " + ANSIColor::coloredString("WRONG", ANSIColor::FG_RED);
        }
    }
    else
    {
        if(suc == SUCCESS)
        {
            res += " | SUCCESS";
        }
        else if(suc == WRONG)
        {
            res += " | WRONG";
        }
    }

    if(format == ADVANCED && errorText.length() != 0)
    {
        res += (" => " + errorText);
    }

    return res;
}

/**
 * @brief LogAdapter::generateUnitMoveLog
 * @param source
 * @param format
 * @param param
 * 1st - X coord source
 * 2nd - Y coord source
 * 3d - X coord dest
 * 4th - Y coord dest
 * @return
 */
std::string LogAdapter::generateUnitMoveLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText)
{
    if(param.size() < 4 && format == ADVANCED)
    {
        throw std::invalid_argument("Invalid number of parameters for logging the unit move");
    }

    std::string res = "";
    if(source == USER_LOG)
    {
        res += "USER: request for unit move";
    }
    else if(source == GAME_LOG)
    {
        res += "GAME: unit move";
    }

    if(format == ADVANCED)
    {
        res += " from (" + std::to_string(param[0]) + ";" + std::to_string(param[1]) + ") to (" + std::to_string(param[2]) + ";" + std::to_string(param[3]) + ")";
    }

    if(logger->getType() == TERMINAL_LOG)
    {
        if(suc == SUCCESS)
        {
            res += " | " + ANSIColor::coloredString("SUCCESS", ANSIColor::FG_GREEN);
        }
        else if(suc == WRONG)
        {
            res += " | " + ANSIColor::coloredString("WRONG", ANSIColor::FG_RED);
        }
    }
    else
    {
        if(suc == SUCCESS)
        {
            res += " | SUCCESS";
        }
        else if(suc == WRONG)
        {
            res += " | WRONG";
        }
    }

    if(format == ADVANCED && errorText.length() != 0)
    {
        res += (" => " + errorText);
    }

    return res;
}

/**
 * @brief LogAdapter::generateInfAboutCellLog
 * @param source
 * @param format
 * @param param
 * 1st - X coord
 * 2nd - Y coord
 * 3d - about whom information is requested (type)
 * @return
 */
std::string LogAdapter::generateInfAboutCellLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText)
{
    if(param.size() < 3 && format == ADVANCED)
    {
        throw std::invalid_argument("Invalid number of parameters for logging the information about the cell");
    }


    std::string res = "";
    if(source == USER_LOG)
    {
        res += "USER : request for cell infromation";
    }
    else if(source == GAME_LOG)
    {
        res += "GAME : cell information";
    }

    if(format == ADVANCED)
    {
        res += " by coords: (" + std::to_string(param[0]) + ";" + std::to_string(param[1]) + ") for " + Command::convertInfoRequestEnumToString(static_cast<eRequest>(param[3]));
    }

    if(logger->getType() == TERMINAL_LOG)
    {
        if(suc == SUCCESS)
        {
            res += " | " + ANSIColor::coloredString("SUCCESS", ANSIColor::FG_GREEN);
        }
        else if(suc == WRONG)
        {
            res += " | " + ANSIColor::coloredString("WRONG", ANSIColor::FG_RED);
        }
    }
    else
    {
        if(suc == SUCCESS)
        {
            res += " | SUCCESS";
        }
        else if(suc == WRONG)
        {
            res += " | WRONG";
        }
    }

    if(format == ADVANCED && errorText.length() != 0)
    {
        res += (" => " + errorText);
    }

    return res;
}

/**
 * @brief LogAdapter::sendLogInf
 * @param source
 * @param event
 * @param param
 */
void LogAdapter::sendLogInf(eLOG_SOURCE source, eLOG_EVENT event, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText)
{
    if(!logger)
    {
        throw std::invalid_argument("Trying to use the logger adapter without installing the logger itself");
    }
    if(logger->getType() == NO_LOG)
    {
        return;
    }

    if(event == USER_GAME_CREATE || event == GAME_CREATE)
    {
        logger->printLog(generateGameCreationLog(source, format, param, suc, errorText));
    }
    else if(event == USER_ADD_UNIT || event == GAME_ADD_UNIT)
    {
        logger->printLog(generateUnitAddLog(source, format, param, suc, errorText));
    }
    else if(event == USER_ADD_BASE || event == GAME_ADD_BASE)
    {
        logger->printLog(generateBaseAddLog(source, format, param, suc, errorText));
    }
    else if(event == USER_ATTACK_UNIT || event == GAME_ATTACK_UNIT)
    {
        logger->printLog(generateUnitAttackLog(source, format, param, suc, errorText));
    }
    else if(event == USER_MOVE_UNIT || event == GAME_MOVE_UNIT)
    {
        logger->printLog(generateUnitMoveLog(source, format, param, suc, errorText));
    }
    else if(event == USER_INF_ABOUT_CELL || event == GAME_INF_ABOUT_CELL)
    {
        logger->printLog(generateInfAboutCellLog(source, format, param, suc, errorText));
    }
}
