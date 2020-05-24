#include "fieldexception.h"

CellException::CellException(std::string error) noexcept
{
    exText = std::move(error);
}

const char* CellException::what() const throw()
{
    return exText.c_str();
}

std::vector<size_t> CellException::getPar()
{
    return param;
}

FieldException::FieldException() noexcept
{
    exText += "Field error:";
}

std::vector<size_t> FieldException::getPar()
{
    return param;
}

CoordsNotPartOfTheField::CoordsNotPartOfTheField(size_t xDest, size_t yDest, size_t widthField, size_t heightField)
{
    param.push_back(xDest);
    param.push_back(yDest);
    param.push_back(widthField);
    param.push_back(heightField);
    exText += " coords (" + std::to_string(param[0]) + ";" + std::to_string(param[1]) + ") not part of the field " + std::to_string(param[2]) + "*" + std::to_string(param[3]);
}

const char* CoordsNotPartOfTheField::what() const throw()
{
    return exText.c_str();
}

SimpleFieldException::SimpleFieldException(std::string error)
{
    exText += " " + error;
}

const char* SimpleFieldException::what() const throw()
{
    return exText.c_str();
}

FieldBusyCellException::FieldBusyCellException(size_t x, size_t y)
{
    param.push_back(x);
    param.push_back(y);
    exText += " on cell (" + std::to_string(x) + ";" + std::to_string(y) + ") already is unit";
}

const char* FieldBusyCellException::what() const throw()
{
    return exText.c_str();
}
