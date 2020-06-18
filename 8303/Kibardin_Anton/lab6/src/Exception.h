//
// Created by anton on 05.05.2020.
//

#ifndef OOP_1_EXCEPTION_H
#define OOP_1_EXCEPTION_H
#include <exception>
#include <string>
class LogicException: public std::exception
{
    std::string m_error;
public:
    explicit LogicException(std::string error, int parameter){
        m_error = error + " : " + std::to_string(parameter);
    }
    const char* what() noexcept { return  m_error.c_str();}
};

class TypeException: public std::exception
{
    std::string m_error;
public:
    explicit TypeException(std::string requestType){
        m_error = "file string must contain type " + requestType;
    }
    const char* what() noexcept { return  m_error.c_str();}
};

class CheckException: public std::exception
{
    std::string m_error;
public:
    explicit CheckException(std::string requestChecker){
        m_error = "incorrect checker " + requestChecker;
    }
    const char* what() noexcept { return  m_error.c_str();}
};
#endif //OOP_1_EXCEPTION_H
