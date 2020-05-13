#pragma once
#include <string>
#include <iostream>
#include "Output.h"
using namespace std;

class LoggerProtected {
private:
	Fwrite* file = new Fwrite("Log.txt");
protected:
	void writeToConsole(string log) 
	{
		cout << "log: " << log << endl;
	}
	void writeToFile(string log) 
	{
		file->write("log:" + log);
	}
};
class Logger : LoggerProtected {

public:
	Logger() {}
protected:
	void print(string log, bool writeAble, bool filewriteAble) 
	{
		if (writeAble)
		{
			if (filewriteAble)
				writeToFile(log);
			else
				writeToConsole(log);
		}
	}
};