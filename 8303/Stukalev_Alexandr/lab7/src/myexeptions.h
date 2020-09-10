#ifndef MYEXEPTIONS_H
#define MYEXEPTIONS_H

#include <exception>
#include <string>
class TypeExceptions: public std::exception
{
    std::string error;
public:
    TypeExceptions(std::string func, std::string wrongparam, std::string correctparam)
    {
        error = "Error: type exception in " + func + " with invalid data " + wrongparam + " and correct data is " + correctparam + "\n";
    }
    TypeExceptions(std::string func, std::string correctparam)
    {
        error = "Error: type exception in " + func + " expected correct data is " + correctparam + "\n";
    }
    TypeExceptions(std::string func, char* wrongparam, std::string correctparam)
    {
        error = "Error: type exception in " + func + " with invalid data " + wrongparam + " and correct data is " + correctparam + "\n";
    }
    const char* what() const noexcept override
    {
        return error.c_str();
    }
};

class OutOfRangeExceptions: public std::exception
{
    std::string error;
public:
    OutOfRangeExceptions(std::string func, std::string wrongparam, std::string correctparam)
    {
        error = "Error: out of range exception in " + func + " with invalid data " + wrongparam + " and correct data is " + correctparam + "\n";
    }
    OutOfRangeExceptions(std::string func, std::string correctparam)
    {
        error = "Error: type exception in " + func + " expected correct data is " + correctparam + "\n";
    }
    OutOfRangeExceptions(std::string func, char* wrongparam, std::string correctparam)
    {
        error = "Error: out of range exception in " + func + " with invalid data " + wrongparam + " and correct data is " + correctparam + "\n";
    }
    const char* what() const noexcept override
    {
        return error.c_str();
    }
};

class LogicalExceptions: public std::exception
{
    std::string error;
public:
    LogicalExceptions(std::string func, std::string wrongparam, std::string correctparam)
    {
        error = "Error: logical exception in " + func + " with invalid data " + wrongparam + " and correct data is " + correctparam + "\n";
    }
    LogicalExceptions(std::string func, std::string correctparam)
    {
        error = "Error: type exception in " + func + " expected correct data is " + correctparam + "\n";
    }
    LogicalExceptions(std::string func, char* wrongparam, std::string correctparam)
    {
        error = "Error: logical exception in " + func + " with invalid data " + wrongparam + " and correct data is " + correctparam + "\n";
    }
    const char* what() const noexcept override
    {
        return error.c_str();
    }
};

#endif // MYEXEPTIONS_H
