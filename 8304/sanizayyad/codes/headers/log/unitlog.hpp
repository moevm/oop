#ifndef unitlog_hpp
#define unitlog_hpp

#include "unit.hpp"
#include <stdio.h>


class UnitLog
{
public:
    static std::string moveMessage(std::shared_ptr<Unit> unit,const Position2D& from, const Position2D& to);

    static std::string createMessage(std::shared_ptr<Unit> unit);

    static std::string dieMessage(std::shared_ptr<Unit> unit);

    static std::string healthMessage(std::shared_ptr<Unit> unit, double damage);

    static std::string attackMessage(std::shared_ptr<Unit> unit, std::shared_ptr<Unit> enemy);

private:
    static std::string getPlayer(std::shared_ptr<Unit> unit);
};


#endif /* unitlog_hpp */
