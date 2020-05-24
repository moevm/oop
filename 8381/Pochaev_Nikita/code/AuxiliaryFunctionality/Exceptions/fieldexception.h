#ifndef FIELDEXCEPTION_H
#define FIELDEXCEPTION_H

#include "baseexception.h"

class CellException : public BaseException
{
public:
    CellException(std::string error) noexcept;
    ~CellException() = default;
    virtual const char* what() const throw();
    virtual std::vector<size_t> getPar();
};

class FieldException : public BaseException
{
public:
    FieldException() noexcept;
    ~FieldException() = default;
    virtual const char* what() const throw() override = 0;
    std::vector<size_t> getPar() override;
};

class CoordsNotPartOfTheField final : public FieldException
{
public:
    CoordsNotPartOfTheField(size_t xDest, size_t yDest, size_t widthField, size_t heightField);
    ~CoordsNotPartOfTheField() = default;
    const char* what() const throw() override;
};

class SimpleFieldException final : public FieldException
{
public:
    SimpleFieldException(std::string error);
    ~SimpleFieldException() = default;
    const char* what() const throw() override;
};

class FieldBusyCellException final : public FieldException
{
public:
    FieldBusyCellException(size_t x, size_t y);
    ~FieldBusyCellException() = default;
    const char* what() const throw() override;
};

#endif // FIELDEXCEPTION_H
