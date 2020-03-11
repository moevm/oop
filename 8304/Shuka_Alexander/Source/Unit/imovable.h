#ifndef IMOVABLE_H
#define IMOVABLE_H


#include "Field/point2d.h"


constexpr const char* MOVE_TOP = "move top";
constexpr const char* MOVE_BOTTOM = "move bottom";
constexpr const char* MOVE_LEFT = "move left";
constexpr const char* MOVE_RIGHT = "move right";


class IMovable
{
public:
    virtual ~IMovable() = default;
    
    virtual Point2D moveLeft() = 0;
    virtual Point2D moveRight() = 0;
    virtual Point2D moveTop() = 0;
    virtual Point2D moveBottom() = 0;
};

#endif // IMOVABLE_H
