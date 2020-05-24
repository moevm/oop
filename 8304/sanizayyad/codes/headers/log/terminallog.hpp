#ifndef terminallog_hpp
#define terminallog_hpp

#include "log.hpp"


#include <stdio.h>
#include <iostream>


class TerminalLog: public Log
{
public:
    explicit TerminalLog() = default;

    virtual void writeTo(const std::string& msg, TYPE type = TYPE::INFO) override;
};

#endif /* terminallog_hpp */
