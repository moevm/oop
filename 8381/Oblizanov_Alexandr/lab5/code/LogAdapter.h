#ifndef LOGADAPTER_H
#define LOGADAPTER_H

#include "logger.h"

class LogAdapter : public ILogAdapter
{
public:
    LogAdapter(ILogger *logger);
    void setLogger(ILogger *logger);
    void pushLog(LogEvent event, std::vector<int> param = {});
    LogType getType() const;
    void setType(const LogType &value);
    ~LogAdapter();
private:
    std::string makeUserActionLog(LogEvent event, std::vector<int> param = {});
    std::string makeGameCreateLog(std::vector<int> param = {});
    std::string makeBaseAddLog(std::vector<int> param = {});
    std::string makeNeutralAddLog(std::vector<int> param = {});
    std::string makeUnitAddLog(std::vector<int> param = {});
    std::string makeBaseUpdateLog(std::vector<int> param = {});
    std::string makeAttackLog(std::vector<int> param = {});
    std::string makeCounterUpdate(std::vector<int> param = {});
    std::string makeMoveLog(std::vector<int> param = {});
    ILogger *logger;
    LogType type;
};

#endif // LOGADAPTER_H
