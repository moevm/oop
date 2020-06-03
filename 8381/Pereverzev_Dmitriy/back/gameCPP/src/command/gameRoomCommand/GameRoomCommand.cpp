
#include "GameRoomCommand.hpp"

GameRoomCommand::GameRoomCommand(GameRoom<Rule> *gameRoom) /* , v8::Isolate *isolate) : Command(isolate) */
{
    

    this->gameRoom = gameRoom;
    
}

void GameRoomCommand::execute(v8::Local<v8::Value> request)
{
    

    v8::Local<v8::Object> objRequest;

    if (request->IsObject())
        objRequest = request->ToObject();
    else
        return;

    /*  */
    unsigned int task;
    v8::Local<v8::Object> params;

    /*  */

    if (!GetObjProperty(objRequest, "task", task))
        return;
    if (!GetObjProperty(objRequest, "params", params))
        return;

    

    if (task == GET_FULL)
    {
        
        try
        {
            
            gameRoom->fireEvent("get full room", gameRoom->getFullInfo());
        }
        catch (Except &except)
        {
            fireEvent("except", except.getLog());
            
        }
    }
    else if (task == ADD_PLAYER)
    {

        /* * * * * */
        v8::Local<v8::Object> playerInfo;
        /*  */ std::string playerID;
        /*  */ std::string playerName;
        /* * * * * */

        if (!GetObjProperty(params, "playerInfo", playerInfo))
            return;
        if (!GetObjProperty(playerInfo, "playerID", playerID))
            return;
        if (!GetObjProperty(playerInfo, "playerName", playerName))
            return;

        

        try
        {
            gameRoom->addPlayer(playerID, playerName); 
        }
        catch (Except &except)
        {
            fireEvent("except", except.getLog());
            
        }
    }
    else
    {
        /* * * * * */
        std::string userID;
        /* * * * * */
        

        Command *command;
        

        if (GetObjProperty(params, "playerID", userID))
        {
            
            if (gameRoom->checkPermission(userID))
            {
                Player *player = gameRoom->getPlayer(userID);
                if (player == nullptr)
                    return;
                

                command = new PlayerCommand(player);
                command->attachEvent("except", this);

                gameRoom->nextPlayer();
            }
            else
            {

                v8::Local<v8::Object> res = Nan::New<v8::Object>();
                gameRoom->SetObjProperty(res, "playerID", userID);
                gameRoom->fireEvent("player does not have permission", res);
                
                return;
            }
            
        }
        else if (GetObjProperty(params, "editorID", userID))
        {
            Editor *editor = gameRoom->getEditor();
            if (editor == nullptr)
                return;
            command = new EditorCommand(editor);
            command->attachEvent("except", this);
        }

        if (task == MOVE)
        {
            command->execute(request);
        }
        else if (task == ADD_OBJ)
        {
            

            command->execute(request);

            

            /* * * * * */
            unsigned int objectType;
            /* * * * * */

            if (!GetObjProperty(params, "objectType", objectType))
                return;
            if (objectType == NEUT_OBJ)
            {
                
            }
            else if (objectType == COMB_OBJ)
            {
                

                
            }
        }

        delete command;
    }
    
}
