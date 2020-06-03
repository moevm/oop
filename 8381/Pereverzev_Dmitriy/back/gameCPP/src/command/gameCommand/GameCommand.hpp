#ifndef GameCommand_hpp
#define GameCommand_hpp

#include "../Command.hpp"
#include "../gameRoomCommand/GameRoomCommand.hpp"
#include "../../game/Game.hpp"

class GameCommand : public Command
{
private:
    Game *game;
    

public:
    GameCommand(Game *game);
    
    void execute(v8::Local<v8::Value> request) override;
};

#endif /* GameCommand_hpp */