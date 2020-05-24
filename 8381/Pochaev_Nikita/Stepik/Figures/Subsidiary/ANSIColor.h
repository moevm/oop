#ifndef STEPIC_ANSICOLOR_H
#define STEPIC_ANSICOLOR_H

#include <ostream>
#include <sstream>
#include <string>

#include "Information.h"

class ANSIColor {
public:
    enum eCOLOR_CODE
    {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_YELLOW   = 33,
        FG_CYAN     = 36,
        FG_MAGENTA  = 35,
        FG_DEFAULT  = 39,

        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };

    ANSIColor() = default;
    ~ANSIColor() = default;
    explicit ANSIColor(eCOLOR_CODE color_);

    static std::string coloredString( const std::string& s, unsigned _clr = 0, unsigned _mode = 0);

    eCOLOR_CODE getColor();
    void setColor(eCOLOR_CODE color);
    static std::string convertFGEnumToStr(eCOLOR_CODE code);
private:
    eCOLOR_CODE color{FG_DEFAULT};
};

#endif //STEPIC_ANSICOLOR_H
