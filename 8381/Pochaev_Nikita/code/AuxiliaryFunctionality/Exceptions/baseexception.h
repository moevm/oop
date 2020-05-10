#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <QtGlobal>

class BaseException : public std::exception
{
public:
    BaseException() = default;
    ~BaseException() noexcept = default;
    // throw() - guaranteed failure
    virtual const char* what() const throw() = 0;
    virtual std::vector<size_t> getPar() = 0;

protected:
    std::string exText{};
    std::vector<size_t> param{};
};

#endif // BASEEXCEPTION_H
