//
// Created by max on 29.04.20.
//

#ifndef OOP_LOG_H
#define OOP_LOG_H

#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::fstream;
using std::ofstream;
using std::cout;
using std::cin;

class Log {
    bool state = false;
public:
    Log()
    {

    }
    ~Log()
    {

    }
    virtual void write(string text) = 0;
    void setState(bool state);
    bool getState();
};

class TerminalLog : public Log{
public:
    TerminalLog()
    {

    }
    ~TerminalLog()
    {

    }
    virtual void write(string text);
};

class FileLog : public  Log{
    ofstream file;
public:
    FileLog(string filename="game_report.txt")
    {
        file.open(filename);
    }
    ~FileLog()
    {
        file.close();
    }
    virtual void write(string text);
};

#endif //OOP_LOG_H
