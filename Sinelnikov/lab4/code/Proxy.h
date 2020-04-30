//
// Created by max on 30.04.20.
//

#ifndef OOP_PROXY_H
#define OOP_PROXY_H

#include "Log.h"
#include "Field.h"

class Proxy {
public:
    Proxy()
    {

    }
    ~Proxy()
    {

    }
    void changeLogType(Field* f, TerminalLog* terminal_log, FileLog* file_log);
};


#endif //OOP_PROXY_H
