#ifndef LABS_EXCEPTIONS_H
#define LABS_EXCEPTIONS_H

#include <string>
#include <exception>

class LogicException: public std::exception {
    std::string err;
public:
    LogicException(std::string when, int type){
        err = "<Error! logic error in " + when + " with param " + std::to_string(type) + ">";
    }

    LogicException(std::string when, std::string type){
        err = "<Error! logic error in " + when + " with param " + type;
    }

    const char *typeOfError() const noexcept  {
        return err.c_str();
    }
};

class InputException: public std::exception {
    std::string err;
public:
    InputException(std::string type){
        err = "<Error! expected data type " + type + " was received another>";
    }

    const char* typeOfError() const noexcept  {
        return err.c_str();
    }
};

#endif //LABS_EXCEPTIONS_H
