#ifndef PlayerCommand_hpp
#define PlayerCommand_hpp

#include "../Command.hpp"
#include "../gameRoomCommand/GameRoomCommand.hpp"
#include "../../player/Player.hpp"

class PlayerCommand : public Command
{
private:
    Player *player;
    

public:
    PlayerCommand(Player *player);
    
    void execute(v8::Local<v8::Value> request) override;
};

#endif /* PlayerCommand_hpp */