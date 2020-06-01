#pragma once
#include <exception>
class GameException : public std::exception
{
	const char* _file;
	int _line;
	const char* _func;
	const char* _info;

public:
	GameException(const char* msg, const char* file, int line, const char* func, const char* info = "") : std::exception(msg),
		_file(file),
		_line(line),
		_func(func),
		_info(info)
	{
	}

	const char* getFile() const { return _file; }
	int getLine() const { return _line; }
	const char* getFunc() const { return _func; }
	const char* getInfo() const { return _info; }
};

