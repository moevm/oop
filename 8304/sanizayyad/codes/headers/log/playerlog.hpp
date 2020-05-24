#ifndef playerlog_hpp
#define playerlog_hpp

#include "unit.hpp"

#include <stdio.h>


class PlayerLog
{
public:
    static std::string createUnit(bool isCreate, PLAYER player);
    static std::string attack(PLAYER player);
    static std::string deffend(PLAYER player);

private:
    static std::string getPlayer(PLAYER player);
};


#endif /* playerlog_hpp */
