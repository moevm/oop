//
// Created by therealyou on 01.06.2020.
//

#ifndef LAB1_EXCEPTION_H
#define LAB1_EXCEPTION_H

#include <exception>
#include <string>

class LogicException : public std::exception {
    std::string m_error;
public:
    template<typename T>
    explicit LogicException(std::string error, T parameter) :
            LogicException(error, std::to_string(parameter)) {
    }

    explicit LogicException(std::string error, std::string parameter) {
        m_error = error + " : " + parameter;
    }

    const char *what() noexcept { return m_error.c_str(); }
};

class CheckException : public std::exception {
    std::string m_error;
public:
    explicit CheckException(std::string requestChecker) {
        m_error = "incorrect checker " + requestChecker;
    }

    const char *what() noexcept { return m_error.c_str(); }
};

class TypeException : public std::exception {
    std::string m_error;
public:
    explicit TypeException(std::string requestType) {
        m_error = "file string must contain type " + requestType;
    }

    const char *what() noexcept { return m_error.c_str(); }
};


#endif //LAB1_EXCEPTION_H
