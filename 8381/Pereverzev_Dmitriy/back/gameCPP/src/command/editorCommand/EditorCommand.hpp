#ifndef EditorCommand_hpp
#define EditorCommand_hpp

#include "../Command.hpp"
#include "../gameRoomCommand/GameRoomCommand.hpp"
#include "../../editor/editor.hpp"

class EditorCommand : public Command
{
private:
    Editor *editor;

public:
    EditorCommand(Editor *editor);

    void execute(v8::Local<v8::Value> request) override;
};

#endif /* EditorCommand_hpp */