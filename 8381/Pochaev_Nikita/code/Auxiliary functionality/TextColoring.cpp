#include "TextColoring.h"

std::string ANSIColor::coloredString(const std::string &s, unsigned int _clr, unsigned int _mode)
{
    std::stringstream result;
    std::string ANSI =  "\033[";
    std::string  clr = std::to_string(_clr);
    std::string  mode = std::to_string(_mode);
    result << ANSI << mode << ";" << clr << "m";
    result << s;
    result << ANSI << FG_DEFAULT << ";" << BG_DEFAULT << "m";
    return result.str();
}