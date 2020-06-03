
#ifndef GameRoomState_hpp
#define GameRoomState_hpp

#include <map>
#include "../../player/Player.hpp"



class GameRoomState
{
protected:
    
    
    Player *nowPlayer;

public:
    bool checkPermission(std::string playerID);
    virtual void nextPlayer() = 0;
};
#endif /* GameRoomState_hpp */
