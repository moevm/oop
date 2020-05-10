#ifndef LOGADAPTER_H
#define LOGADAPTER_H

#include "ILogAdapter.h"
#include "Game/Logging/ILogger.h"

// ha-ha absolute path without CLion refactoriing
#include "../../../AuxiliaryFunctionality/TextColoring.h"

class LogAdapter : public ILogAdapter, public ILogAdapterStringFormer
{
public:
    ~LogAdapter() = default;
    LogAdapter() = default;
    LogAdapter(std::shared_ptr<ILogger>);

    void setLogger(std::shared_ptr<ILogger> logger_) override;
    void setOutputFormat(eLOGGER_OUTPUT_FORMAT format_) override;
    void sendLogInf(eLOG_SOURCE source, eLOG_EVENT event, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText) override;

private:
    eLOGGER_OUTPUT_FORMAT format{STANDART};
    std::shared_ptr<ILogger> logger{};

    std::string generateGameCreationLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText = {}) override;
    std::string generateUnitAddLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText = {}) override;
    std::string generateBaseAddLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText = {}) override;
    std::string generateUnitAttackLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText = {}) override;
    std::string generateUnitMoveLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText = {}) override;
    std::string generateInfAboutCellLog(eLOG_SOURCE source, eLOGGER_OUTPUT_FORMAT format, std::vector<size_t> param, eSUCCESSFULNESS suc, std::string errorText = {}) override;
};

#endif // LOGADAPTER_H
