#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class LogicException: public std::exception{
private:
    std::string error;

public:
    LogicException(std::string place, int parameter){
        error = "Error: logic exception in " + place + " with incorrect parameter " + std::to_string(parameter);
    }

    LogicException(std::string place, std::string parameter){
        error = "Error: logic exception in " + place + " with incorrect parameter " + parameter;
    }

    const char* what() const noexcept override {
        return error.c_str();
    }
};

class TypeInputException: public std::exception{
private:
    std::string error;

public:
    TypeInputException(std::string type){
        error = "Error: expected data type " + type + " but another was received";
    }

    const char* what() const noexcept override {
        return error.c_str();
    }
};

#endif // EXCEPTIONS_H
