#ifndef GameRoomCommand_hpp
#define GameRoomCommand_hpp

#include "../Command.hpp"
#include "../playerCommand/PlayerCommand.hpp"
#include "../editorCommand/EditorCommand.hpp"
#include "../../gameRoom/GameRoom.hpp"

class GameRoomCommand : public Command
{
private:
    GameRoom<Rule> *gameRoom;

public:
    GameRoomCommand(GameRoom<Rule> *gameRoom);
    void execute(v8::Local<v8::Value> request) override; 
};

#endif /* GameRoomCommand_hpp */