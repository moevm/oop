
#include "LoggerAdapter.hpp"

LoggerAdapter::LoggerAdapter()
{
    this->status = true;
}

LoggerAdapter::LoggerAdapter(bool status)
{
    this->status = status;
}

std::string
LoggerAdapter::adaptFormat(v8::Local<v8::Object> objLog)
{

    
    std::string strLogType;
    GetObjProperty(objLog, "logType", strLogType);

    
    std::string strLogData;
    v8::Local<v8::Object> objLogData = Nan::New<v8::Object>();
    GetObjProperty(objLog, "data", objLogData);
    strLogData = JSONStringified(objLogData);

    
    std::time_t logTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string strLogTime(std::ctime(&logTime));

    
    std::string strLog = strLogType + ";" + strLogData + ";" + strLogTime;

    return strLog;
}

void LoggerAdapter::setStatus(bool status)
{
    this->status = status;
}

bool LoggerAdapter::getStatus()
{
    return this->status;
}
