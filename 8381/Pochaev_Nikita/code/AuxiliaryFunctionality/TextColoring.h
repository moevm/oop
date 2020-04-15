#ifndef OOP_TEXTCOLORING_H
#define OOP_TEXTCOLORING_H

#include <ostream>
#include <sstream>
#include <string>

/**
 * INCLUDES ONLY ONES IN PROGRAM
 */
namespace ANSIColor
{
    enum Code
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

    std::string coloredString( const std::string& s, unsigned _clr = 0, unsigned _mode = 0);
}

#endif //OOP_TEXTCOLORING_H
