#ifndef ILOGADAPTER_H
#define ILOGADAPTER_H

#include <memory>
#include <vector>

#include "Game/Logging/logfunctionality.h"

class ILogger;

class ILogAdapter
{
public:
    virtual ~ILogAdapter() = default;
    virtual void setLogger(std::shared_ptr<ILogger> logger_) = 0;
    virtual void setOutputFormat(eLOGGER_OUTPUT_FORMAT format_) = 0;
    virtual void sendLogInf(eLOG_SOURCE source, eLOG_EVENT event, std::vector<size_t> param = {}, eSUCCESSFULNESS suc = UNKNOWN, std::string errorText = "") = 0;
};

class ILogAdapterStringFormer
{
protected:
    virtual std::string generateGameCreationLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText) = 0;
    virtual std::string generateUnitAddLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText) = 0;
    virtual std::string generateBaseAddLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText) = 0;
    virtual std::string generateUnitAttackLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText) = 0;
    virtual std::string generateUnitMoveLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText) = 0;
    virtual std::string generateInfAboutCellLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText) = 0;
};

#endif // ILOGADAPTER_H
