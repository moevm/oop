
#include "GameCommand.hpp"
GameCommand::GameCommand(Game *game) /* , v8::Isolate *isolate) : Command(isolate) */
{
    
    this->game = game;

    
}

void GameCommand::execute(v8::Local<v8::Value> request)
{

    

    v8::Local<v8::Object> objRequest;

    if (request->IsObject())
        objRequest = request->ToObject();
    else
        return;

    /* * * * * */
    unsigned int task;
    if (!GetObjProperty(objRequest, "task", task))
        return;

    if (task == ROOMS_LIST)
    {
        game->fireEvent("tabel of GameRooms update", game->getGameRoomsInfo());
        return;
    }

    v8::Local<v8::Object> params;
    /*  */ std::string roomID;
    /* * * * * */
    if (!GetObjProperty(objRequest, "params", params))
        return;
    if (!GetObjProperty(params, "roomID", roomID))
        return;

    if (task == ADD_ROOM)
    {
        

        /* * * * * */
        std::string roomName;
        std::string editorID;
        unsigned int rule;
        v8::Local<v8::Object> fieldInfo;
        /*  */ unsigned int rowsQuantity;
        /*  */ unsigned int columnsQuantity;
        /*  */ unsigned int maximumObjectsQuantity;
        /* * * * * */

        if (!GetObjProperty(params, "editorID", editorID))
            return;
        if (!GetObjProperty(params, "roomName", roomName))
            return;
        if (!GetObjProperty(params, "rule", rule))
            return;
        if (!GetObjProperty(params, "fieldInfo", fieldInfo))
            return;
        if (!GetObjProperty(fieldInfo, "rowsQuantity", rowsQuantity))
            return;
        if (!GetObjProperty(fieldInfo, "columnsQuantity", columnsQuantity))
            return;
        

        this->game->addGameRoom(editorID, roomID, roomName, rowsQuantity, columnsQuantity, rule); 
        
    }
    else if (task == SAVE_ROOM || task == LOAD_ROOM)
    {
        std::string editorID;
        if (!GetObjProperty(params, "editorID", editorID))
            return;
        
        if (task == SAVE_ROOM)
        {
            game->saveRoom(editorID, roomID); 
        }
        else if (task == LOAD_ROOM)
        {
            unsigned int saveID;
            if (!GetObjProperty(params, "saveID", saveID))
                return;
            game->loadRoom(editorID, roomID, saveID); 
        }
        
    }
    else if (task == GET_FULL || task == ADD_OBJ || task == ADD_PLAYER || task == MOVE)
    {
        GameRoomCommand *gameRoomCommand = new GameRoomCommand(game->getGameRoom(roomID) /* , isolate */);
        gameRoomCommand->attachEvent("except", this);

        
        gameRoomCommand->execute(request);

        delete gameRoomCommand;
        
    }

    
}
