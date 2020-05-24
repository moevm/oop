#include "ANSIColor.h"

ANSIColor::ANSIColor(eCOLOR_CODE color_) : color(color_) { }

std::string ANSIColor::coloredString(const std::string &s, unsigned int _clr, unsigned int _mode) {
    std::stringstream result;
    std::string ANSI =  "\033[";
    std::string  clr = std::to_string(_clr);
    std::string  mode = std::to_string(_mode);
    result << ANSI << mode << ";" << clr << "m";
    result << s;
    result << ANSI << FG_DEFAULT << ";" << BG_DEFAULT << "m";
    return result.str();
}

ANSIColor::eCOLOR_CODE ANSIColor::getColor() {
    return color;
}

void ANSIColor::setColor(ANSIColor::eCOLOR_CODE color_) {
    color = color_;
}

std::string ANSIColor::convertFGEnumToStr(ANSIColor::eCOLOR_CODE code) {
    if(code == FG_RED) {
        return "Red";
    } else if(code == FG_GREEN) {
        return "Green";
    } else if(code == FG_BLUE) {
        return "Blue";
    } else if(code == FG_YELLOW) {
        return "Yellow";
    } else if(code == FG_CYAN) {
        return "Cyan";
    } else if(code == FG_MAGENTA) {
        return "Magenta";
    } else if(code == FG_DEFAULT) {
        return "Default";
    }

    return "No FG color";
}

