#pragma once
#include <fstream>
#include <string>
#include <QDebug>

#define LOG_F_NAME "log.txt"

class Logger
{
public:
	static void setLoggingMode(int mode);	//0 - no logging, 1 - to console, 2 - to console & to file
	static void setVerboseLevel(int verbose);
	static void log(std::string prefix, std::string msg, int verbose = 3);
protected:
	static int _mode;
	static int _verboseLevel;
	static std::fstream* _fstream;
};

