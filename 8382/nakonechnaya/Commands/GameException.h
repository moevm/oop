#ifndef OOP_GAMEEXCEPTION_H
#define OOP_GAMEEXCEPTION_H
#include <exception>
#include <iostream>
using std::exception;
class GameException : public std::exception
{
    const char* _file;
    int _flag;
    const char* _func;
    const char* _info;

public:
    GameException(const char* file, int flag, const char* func, const char* info = "") :
        _file(file),
        _flag(flag),
        _func(func),
        _info(info)
    {
    }

    const char* getFile() const { return _file; }
    int getFlag() const { return _flag; }
    const char* getFunc() const { return _func; }
    const char* getInfo() const { return _info; }
};
#endif //OOP_GAMEEXCEPTION_H
